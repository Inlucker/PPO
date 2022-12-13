#include "Canvas.h"

#include <QMessageBox>

#include "Settings.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent) //old constructor
{
    user_controller = make_unique<UserController>();
    users_repository = make_shared<USER_REP>();
    canvas_repository = make_shared<CANVAS_REP>();
    params_repository = make_shared<PARAMS_REP>();
    //users_repository = users_rep;
    //canvas_repository = canvas_rep;

    heights_map_points = user_controller->getHeightsMapPoints();
    tri_pol_mas =  user_controller->getTriPolArray();
    zbuffer_alg = user_controller->getZBufferAlg();
    frame_buffer = zbuffer_alg->getFrameBuffer();

    img_width = 960; //1280; //720;
    img_height = 540; //720; //405;
    user_controller->setWidth(img_width);
    user_controller->setHeight(img_height);
    setFixedSize(img_width+2, img_height+2);
    setStyleSheet("border-style: solid; border-width: 1px; border-color: black; background-color:white;");

    setLandscapeColor(20, 150, 20);

    draw_alg = ZBUFFER_PARAM;

    my_img.reset();
    frame_buffer.reset();
    cleanQImage();

    threads_number = 8;
}

Canvas::~Canvas()
{
    /*if (painter->isActive())
        painter->end();*/
}

void Canvas::createCanvas(double range, bool smooth, string name)
{
    int r, g, b, u_id;
    user_controller->getColor(r, g, b);
    u_id = user_controller->getUser()->getId();
    //string name = "CanvasName";
    CanvasBL cbl = CanvasBL(0, u_id, name, *(user_controller->getHeightsMap()), *heights_map_points, r, g, b);
    canvas_repository->addCanvas(cbl);
    updateCanvasesList();

    shared_ptr<CanvasBL> cbl_new = canvas_repository->getCanvas(name);
    //qDebug() << QString::fromStdString(name);
    //qDebug() << cbl_new->getId();
    //int r, g, b;
    user_controller->getColor(r, g, b);
    ParamsBL params_bl(cbl_new->getId(),
                       user_controller->getImgWidth(),
                       user_controller->getImgHeight(),
                       range,
                       smooth,
                       user_controller->getMult(),
                       r, g, b,
                       user_controller->getHeightsMap()->getSize());
    params_repository->addParams(params_bl);
}

void Canvas::deleteCanvas(int id)
{
    canvas_repository->deleteCanvas(id);
}

shared_ptr<ParamsBL> Canvas::selectCanvas(int id)
{
    cleanQImage();

    shared_ptr<CanvasBL> canvas_bl = canvas_repository->getCanvas(id);
    int r, g, b;
    canvas_bl->getColor(r, g, b);

    //user_controller->selectCanvas(c);
    user_controller->selectCanvas(make_shared<LandscapeCanvas>(canvas_bl->getHeightsMap(), canvas_bl->getHeightsMapPoints(), r, g, b));

    heights_map_points = user_controller->getHeightsMapPoints();
    tri_pol_mas =  user_controller->getTriPolArray();
    //zbuffer_alg = user_controller->getZBufferAlg();
    //frame_buffer = zbuffer_alg->getFrameBuffer();

//#ifdef PARAMS
    shared_ptr<ParamsBL> params_bl = params_repository->getParams(id);

    user_controller->setWidth(params_bl->getWidth());
    user_controller->setHeight(params_bl->getHeight());
    user_controller->setRange(params_bl->getRange());
    user_controller->setSmoothing(params_bl->getSmooth());
    user_controller->setMult(params_bl->getMult());

//#endif

    drawLandScape();
    return params_bl;
}

void Canvas::updateCanvas(int id)
{
    int r, g, b, u_id;
    user_controller->getColor(r, g, b);
    u_id = user_controller->getUser()->getId();
    string name = "CanvasName";
    CanvasBL canvas_bl = CanvasBL(id, u_id, name, *(user_controller->getHeightsMap()), *heights_map_points, r, g, b);
    canvas_repository->updateCanvas(canvas_bl, id);
}

//#define ITERS (1025*1025*10)

void Canvas::generateNewLandscape(int size)
{
    cleanQImage();
    user_controller->generateNewLandscape(size);

    heights_map_points = user_controller->getHeightsMapPoints();
    tri_pol_mas =  user_controller->getTriPolArray();
    zbuffer_alg = user_controller->getZBufferAlg();
    frame_buffer = zbuffer_alg->getFrameBuffer();

    drawLandScape();
}

void Canvas::readFromFile(string file_name)
{
    cleanQImage();

    user_controller->readFromFile(file_name);
    heights_map_points = user_controller->getHeightsMapPoints();
    tri_pol_mas =  user_controller->getTriPolArray();
    zbuffer_alg = user_controller->getZBufferAlg();

    drawLandScape();
}

void Canvas::writeToFile(string file_name)
{
    user_controller->writeToFile(file_name);
}

void Canvas::draw()
{
    drawLandScape();
}

void Canvas::cleanQImage()
{
    //cout << "Canvas Width = "<< width() << "; Canvas Height = " << height() << endl;
    my_img = make_unique<QImage>(img_width, img_height, QImage::Format_RGB32);
    my_img->fill(Qt::white);

    update();
}

void Canvas::resetHeightsMap()
{
    user_controller->resetHeightsMap();
}

void Canvas::updateResolution()
{
    setFixedSize(img_width+2, img_height+2);
    zbuffer_alg = user_controller->getZBufferAlg();
    user_controller->updateResolution();
    drawLandScape();
}

void Canvas::setWidth(int new_width)
{
    img_width = new_width;
    user_controller->setWidth(new_width);
}

void Canvas::setHeight(int new_height)
{
    img_height = new_height;
    user_controller->setHeight(new_height);
}

void Canvas::setScale(double new_scale)
{
    //cout << "SCALE" << endl;
}

void Canvas::setRange(float new_range)
{
    user_controller->setRange(new_range);
}

void Canvas::setSmoothing(bool new_smoothing)
{
    user_controller->setSmoothing(new_smoothing);
}

void Canvas::setDrawAlg(DrawAlg alg)
{
    draw_alg = alg;
    drawLandScape();
}

void Canvas::setMult(int new_mult)
{
    user_controller->setMult(new_mult);
    drawLandScape();
}

void Canvas::setLandscapeColor(int r, int g, int b)
{
    user_controller->setLandscapeColor(r, g, b);
    drawLandScape();
}

void Canvas::transform(const Point &move, const Point &scale, const Point &rotate)
{
    user_controller->transform(move, scale, rotate);
}

void Canvas::move(const Point &move)
{
    user_controller->move(move);
}

void Canvas::scale(const Point &scale)
{
    user_controller->scale(scale);
}

void Canvas::rotate(const Point &rotate)
{
    user_controller->rotate(rotate);
}

QColor Canvas::getColor() const
{
    int r, g, b;
    user_controller->getColor(r, g, b);
    return QColor(r, g, b);
}

int Canvas::getMult() const
{
    return user_controller->getMult();
}

shared_ptr<HeightsMapPoints> Canvas::getHeightsMapPoints() const
{
    return user_controller->getHeightsMapPoints();
}

shared_ptr<TriPolArray> Canvas::getTriPolArray() const
{
    return user_controller->getTriPolArray();
}

shared_ptr<LandscapeCanvas> Canvas::getLandscapeCanvas() const
{
    return user_controller->getLandscapeCanvas();
}

void Canvas::setThreadsNumber(int n)
{
    threads_number = n;
}

void Canvas::testUser(string &str)
{
    canvas_repository->test(str);
}

void Canvas::deleteUser()
{
    users_repository->deleteUser(user_controller->getUser()->getId());
}

vector<pair<int, string>> Canvas::updateCanvasesList()
{
    vector<pair<int, string>> vec = canvas_repository->getCanvasesByUid(user_controller->getUser()->getId());
    return vec;
}

void Canvas::login(shared_ptr<UserBL> user_bl)
{
    user_controller->login(user_bl);
    //canvas_repository->setRole(user_bl->getRole(), user_bl->getRole());
    //users_repository->setRole(user_bl->getRole(), user_bl->getRole());
    QVariant r(QString::fromStdString(user_bl->getRole()));
    //qDebug() << "before" << Settings::get(Settings::DBUser, Settings::DataBase).toString();
    Settings::set(Settings::DBUser, Settings::DataBase) = r;
    Settings::set(Settings::DBPass, Settings::DataBase) = r;
    //qDebug() << "after" << Settings::get(Settings::DBUser, Settings::DataBase).toString();
}

void Canvas::logout()
{
    user_controller->logout();
}

shared_ptr<UserBL> Canvas::getUser()
{
    return user_controller->getUser();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        LMB_is_pressed = false;

    if (event->button() == Qt::RightButton)
        RMB_is_pressed = false;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    previous_x = event->x();
    previous_y = event->y();
    if (event->button() == Qt::LeftButton && !LMB_is_pressed && this->rect().contains(event->pos()))
        LMB_is_pressed = true;

    if (event->button() == Qt::RightButton && !RMB_is_pressed && this->rect().contains(event->pos()))
        RMB_is_pressed = true;
}

#define ROTATE_SPEED 5
#define MOVE_SPEED getMult()

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (LMB_is_pressed)
    {
        double x = double(previous_x - event->x()) / ROTATE_SPEED;
        double y = double(previous_y - event->y()) / ROTATE_SPEED;

        //heights_map_points->transform(Point(0, 0, 0), Point(1, 1, 1), Point(-y, -x, 0));
        rotate(Point(-y, -x, 0));

        cleanQImage();
        drawLandScape();
    }
    else if (RMB_is_pressed)
    {
        double x = double(previous_x - event->x()) / MOVE_SPEED;
        double y = double(previous_y - event->y()) / MOVE_SPEED;

        //heights_map_points->transform(Point(-x, -y, 0), Point(1, 1, 1), Point(0, 0, 0));
        move(Point(-x, -y, 0));

        cleanQImage();
        drawLandScape();
    }

    update();

    previous_x = event->x();
    previous_y = event->y();
}

#define SCALE_SPEED 10

void Canvas::wheelEvent(QWheelEvent *event)
{

    QPoint numDegrees = event->angleDelta() / 120;
    double ky = 1 + double(numDegrees.y()) / SCALE_SPEED;

    //heights_map_points->transform(Point(0, 0, 0), Point(ky, ky, ky), Point(0, 0, 0));
    scale(Point(ky, ky, ky));

    cleanQImage();
    drawLandScape();
}

void Canvas::paintEvent(QPaintEvent *)
{
    //painter->drawImage(1, 1, *my_img);
    QPainter pixmap_painter(this);

    pixmap_painter.drawImage(1, 1, *my_img);
}

int Canvas::sign(double val)
{
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    else
        return 0;
}

void Canvas::plotImg(int x, int y, QColor c)
{
    my_img->setPixelColor(x, y, c);
}

void Canvas::plotXImg(int x, int y, QColor c, int m)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if ((m*x)+i < img_width && (m*x)+i >= 0 && (m*y)+j < img_height && (m*y)+j >= 0)
            {
                my_img->setPixelColor((m*x)+i, (m*y)+j, c);
            }
}

void Canvas::drawImageFT(int i0, int i1)
{
    for (int i = i0; i <= i1; i++)
        for (int j = 0; j < frame_buffer->getWidth();  j++)
        {
            color_t c = (*frame_buffer)(i, j);
            int r, g ,b;
            c.getRgb(&r, &g, &b);
            plotXImg(i, j, QColor(r, g, b), MULT);
        }
}

void Canvas::DrawLineBrezenheimFloat(const Point& p1, const Point& p2, QColor c)
{
    DrawLineBrezenheimFloat(p1.getX(), p1.getY(), p2.getX(), p2.getY(), c);
}

void Canvas::DrawLineBrezenheimFloat(double X_start, double Y_start, double X_end, double Y_end, QColor c)
{
    int X1 = round(X_start), Y1 = round(Y_start), X2 = round(X_end), Y2 = round(Y_end);
    int X = X1, Y = Y1;
    int dX = X2 - X1, dY = Y2 - Y1;
    int SX = sign(dX), SY = sign(dY);
    dX = abs(dX), dY = abs(dY);

    int steep;
    if (dY >= dX)
    {
        //dX, dY = dY, dX;
        int tmp = dX;
        dX = dY;
        dY = tmp;
        steep = 1; // шагаем по y
    }
    else
        steep = 0;

    double tg = double(dY) / double(dX) ; // tангенс угла наклона
    double er = tg - 0.5; // начальное значение ошибки

    /*if (!(X >= img_width || X < 0 || Y >= img_height || Y < 0))
        plotImg(X, Y, Qt::black);*/
    plotXImg(X, Y, c, MULT);
    while (X != X2 || Y != Y2)
    {
        if (er >= 0)
        {
            if (steep == 1) // dy >= dx
                X += SX;
            else // dy < dx
                Y += SY;
            er -= 1; // отличие от целого
        }
        if (er <= 0)
        {
            if (steep == 0) // dy < dx
                X += SX;
            else // dy >= dx
                Y += SY;
            er += tg; // отличие от целого
        }
        /*if (!(X >= img_width || X < 0 || Y >= img_height || Y < 0))
            plotImg(X, Y, Qt::black);*/
        plotXImg(X, Y, c, MULT);
    }
}

void Canvas::drawLandScape()
{
    cleanQImage();
    switch (draw_alg)
    {
    case CARCAS:
        carcasDraw();
        break;
    case TRIANGULAR:
        triangularDraw();
        break;
    case ZBUFFER_PARAM:
        zbufferParamDraw();
        break;
    case ZBUFFER_INTERPOLATION:
        zbufferInterpolationDraw();
        break;
    case ZBUFFER_PARAM_THREADS:
        zbufferParamDrawWithThreads();
        break;
    default:
        QMessageBox::information(this, "Error", "No such DrawAlg");//?
        break;
    }
    update();
}

void Canvas::carcasDraw()
{
    //painter->setPen(Qt::black);
    //int HMPsize = heights_map_points->getSize();
    int HMPwidth = heights_map_points->getWidth();
    int HMPheights = heights_map_points->getHeight();
    for (int i = 0; i < HMPheights; i++)
        for (int j = 1; j < HMPwidth; j++)
        {
            shared_ptr<Point> tmp_point1 = (*heights_map_points)(i, j-1);

            shared_ptr<Point> tmp_point2 = (*heights_map_points)(i, j);
            DrawLineBrezenheimFloat(tmp_point1->getX(), tmp_point1->getY(), tmp_point2->getX(), tmp_point2->getY(), getColor());
        }
    for (int i = 1; i < HMPheights; i++)
        for (int j = 0; j < HMPwidth; j++)
        {
            shared_ptr<Point> tmp_point1 = (*heights_map_points)(i-1, j);

            shared_ptr<Point> tmp_point2 = (*heights_map_points)(i, j);

            DrawLineBrezenheimFloat(tmp_point1->getX(), tmp_point1->getY(), tmp_point2->getX(), tmp_point2->getY(), getColor());
        }
}

void Canvas::triangularDraw()
{
    //tri_pol_mas->updatePoints(*heights_map_points);
    for (auto &tri_pol : *tri_pol_mas)
    {
        DrawLineBrezenheimFloat(tri_pol.getP1(), tri_pol.getP2(), getColor());
        DrawLineBrezenheimFloat(tri_pol.getP2(), tri_pol.getP3(), getColor());
        DrawLineBrezenheimFloat(tri_pol.getP3(), tri_pol.getP1(), getColor());
    }
}

void Canvas::zbufferParamDraw()
{
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
            color_t c = (*frame_buffer)(i, j);
            int r, g ,b;
            c.getRgb(&r, &g, &b);
            plotXImg(i, j, QColor(r, g, b), user_controller->getMult());
            //double intensity = (*frame_buffer)(i, j);
            //plotXImg(i, j, QColor(red * intensity, green * intensity, blue * intensity), MULT);
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "paint time = " << seconds << " secs" << endl;
}

void Canvas::zbufferParamDrawWithThreads()
{
    //UPDATE POINTS
    /*clock_t start = clock();
    tri_pol_mas->update2(threads_number); //WITH THREADS
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "tri_pol_mas->update() time = " << seconds << " secs" << endl;

    //Z-BUFFER ALGORITHM
    start = clock();
    zbuffer_alg->executeWithThreads(*tri_pol_mas, threads_number); //WITH THREADS
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "zbuffer_alg->execute() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();
    //cout << *frame_buffer << endl;

    //PAINT
    start = clock();

    int threadsN = threads_number;
    int x[threadsN];
    int dx = frame_buffer->getHeight()/threadsN;
    x[0] = 0;
    for (int i = 1; i < threadsN; i++)
    {
        x[i] = x[i-1] + dx;
    }

    std::thread *th = new std::thread[threadsN];
    for (int i = 0; i < threadsN-1; i++)
    {
        th[i] = std::thread(&Canvas::drawImageFT, this, x[i], x[i+1]);
    }
    th[threadsN-1] = std::thread(&Canvas::drawImageFT, this, x[threadsN-1], frame_buffer->getHeight() - 1);

    for (int i = 0; i < threadsN; i++)
    {
        th[i].join();
    }
    delete[] th;

    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "paint time = " << seconds << " secs" << endl;*/
}

void Canvas::zbufferInterpolationDraw()
{
    //Z-BUFFER ALGORITHM
    clock_t start = clock();
    zbuffer_alg->execute2(*tri_pol_mas);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "zbuffer_alg->execute2() time = " << seconds << " secs" << endl;

    frame_buffer = zbuffer_alg->getFrameBuffer();

    //PAINT
    start = clock();
    ConstIterator<color_t> It = frame_buffer->cbegin();
    for (int i = 0; i < frame_buffer->getHeight() && It != frame_buffer->cend(); i++)
    {
        for (int j = 0; j < frame_buffer->getWidth() && It != frame_buffer->cend(); It++, j++)
        {
            color_t c = (*frame_buffer)(i, j);
            int r, g ,b;
            c.getRgb(&r, &g, &b);
            plotXImg(i, j, QColor(r, g, b), user_controller->getMult());
            //double intensity = (*frame_buffer)(i, j);
            //plotXImg(i, j, QColor(red * intensity, green * intensity, blue * intensity), MULT);
        }
    }
    end = clock();
    seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //cout << "paint time = " << seconds << " secs" << endl;
}


