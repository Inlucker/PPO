#include "ModeratorCanvasWindow.h"
#include "ui_ModeratorCanvasWindow.h"

#include <QMessageBox>

ModeratorCanvasWindow::ModeratorCanvasWindow(int u_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeratorCanvasWindow),
    user_id(u_id)
{
    ui->setupUi(this);

    users_repository = make_shared<USER_REP>();
    canvas_repository = make_shared<CANVAS_REP>();
    controller = make_unique<ModeratorCanvasesController>();

    //canvas = make_unique<QWidget>();
    //canvas->show();
    //ui->scrollArea->setWidget(&(*canvas));
    img_width = controller->getImgWidth();
    img_height = controller->getImgHeight();
    ui->scrollArea->hide();

    cleanQImage();
}

ModeratorCanvasWindow::~ModeratorCanvasWindow()
{
    delete ui;
}

void ModeratorCanvasWindow::setId(int id)
{
    user_id = id;
    updateList();
}

void ModeratorCanvasWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        LMB_is_pressed = false;

    if (event->button() == Qt::RightButton)
        RMB_is_pressed = false;
}

void ModeratorCanvasWindow::mousePressEvent(QMouseEvent *event)
{
    previous_x = event->position().x();
    previous_y = event->position().y();
    if (event->button() == Qt::LeftButton && !LMB_is_pressed && this->rect().contains(event->pos()))
        LMB_is_pressed = true;

    if (event->button() == Qt::RightButton && !RMB_is_pressed && this->rect().contains(event->pos()))
        RMB_is_pressed = true;
}

#define ROTATE_SPEED 5
#define MOVE_SPEED controller->getMult()

void ModeratorCanvasWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (LMB_is_pressed)
    {
        double x = double(previous_x - event->position().x()) / ROTATE_SPEED;
        double y = double(previous_y - event->position().y()) / ROTATE_SPEED;

        //heights_map_points->transform(Point(0, 0, 0), Point(1, 1, 1), Point(-y, -x, 0));
        controller->rotate(Point(-y, -x, 0));

        cleanQImage();
        drawLandScape();
    }
    else if (RMB_is_pressed)
    {
        double x = double(previous_x - event->position().x()) / MOVE_SPEED;
        double y = double(previous_y - event->position().y()) / MOVE_SPEED;

        //heights_map_points->transform(Point(-x, -y, 0), Point(1, 1, 1), Point(0, 0, 0));
        controller->move(Point(-x, -y, 0));

        cleanQImage();
        drawLandScape();
    }

    update();

    previous_x = event->position().x();
    previous_y = event->position().y();
}

#define SCALE_SPEED 10

void ModeratorCanvasWindow::wheelEvent(QWheelEvent *event)
{

    QPoint numDegrees = event->angleDelta() / 120;
    double ky = 1 + double(numDegrees.y()) / SCALE_SPEED;

    //heights_map_points->transform(Point(0, 0, 0), Point(ky, ky, ky), Point(0, 0, 0));
    controller->scale(Point(ky, ky, ky));

    cleanQImage();
    drawLandScape();
}

void ModeratorCanvasWindow::paintEvent(QPaintEvent *)
{
    //painter->drawImage(1, 1, *my_img);
    QPainter pixmap_painter(this);

    pixmap_painter.drawImage(1, 1, *my_img);
}

void ModeratorCanvasWindow::updateList()
{
    vector<pair<int, string>> vec = canvas_repository->getCanvasesByUid(user_id);
    ui->canvases_listWidget->clear();
    for (auto &elem : vec)
    {
        //ui->my_canvases_listWidget->addItem(QString::fromStdString(elem.second));
        QListWidgetItem* new_item = new QListWidgetItem(QString::fromStdString(elem.second));
        new_item->setStatusTip(QString::number(elem.first));
        ui->canvases_listWidget->addItem(new_item);
    }
}

void ModeratorCanvasWindow::plotXImg(int x, int y, QColor c, int m)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if ((m*x)+i < img_width && (m*x)+i >= 0 && (m*y)+j < img_height && (m*y)+j >= 0)
            {
                my_img->setPixelColor((m*x)+i, (m*y)+j, c);
            }
}

void ModeratorCanvasWindow::drawLandScape()
{
    shared_ptr<TriPolArray> tri_pol_mas = controller->getTriPolArray();
    shared_ptr<ZBufferAlg> zbuffer_alg = controller->getZBufferAlg();
    shared_ptr<FrameBuffer> frame_buffer = controller->getFrameBuffer();

    //UPDATE POINTS
    clock_t start = clock();
    //tri_pol_mas = heights_map3->createTriPolMas();
    //tri_pol_mas->updatePoints(*heights_map_points);
    tri_pol_mas->update();
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "tri_pol_mas->update() time = " << seconds << " secs" << endl;

    //Z-BUFFER ALGORITHM
    start = clock();
    zbuffer_alg->execute(*tri_pol_mas);
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "zbuffer_alg->execute() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();
    //cout << *frame_buffer << endl;

    //PAINT
    start = clock();
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            plotXImg(i, j, (*frame_buffer)(i, j), controller->getMult());
            //double intensity = (*frame_buffer)(i, j);
            //plotXImg(i, j, QColor(red * intensity, green * intensity, blue * intensity), MULT);
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "paint time = " << seconds << " secs" << endl;
}

void ModeratorCanvasWindow::cleanQImage()
{
    my_img = make_unique<QImage>(img_width, img_height, QImage::Format_RGB32);
    my_img->fill(Qt::white);

    update();
}

void ModeratorCanvasWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button in ModeratorCanvasWindow";
    this->hide();
    emit exit();
}


void ModeratorCanvasWindow::on_load_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed LOAD button in ModeratorCanvasWindow";
        QList list = ui->canvases_listWidget->selectedItems();
        if (list.size()>0)
        {
            int id = list[0]->statusTip().toInt();
            cleanQImage();

            shared_ptr<CanvasBL> canvas_bl = canvas_repository->getCanvas(id);
            int r, g, b;
            canvas_bl->getColor(r, g, b);

            //user_controller->selectCanvas(c);
            controller->selectCanvas(make_shared<LandscapeCanvas>(canvas_bl->getHeightsMap(), canvas_bl->getHeightsMapPoints(), r, g, b));

            drawLandScape();
        }
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void ModeratorCanvasWindow::on_load_btn_2_clicked()
{
    qInfo(logUserAction()) << "Pressed CLEAR button in ModeratorCanvasWindow";
    controller->cleanCanvas();
    cleanQImage();
    update();
}

