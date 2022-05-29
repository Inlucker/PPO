#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->size_value_label->setStyleSheet("border-style: solid; border-width: 1px; border-color: black; background-color: white");
    ui->color_label->setStyleSheet("background-color: rgb(20, 150, 20)");

    canvas = make_unique<Canvas>();

    ui->scrollArea->setWidget(&(*canvas));

    ui->scale_groupBox->hide();

    unit_tests_window = make_unique<UnitTestsWindow>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login(shared_ptr<UserBL> user_bl)
{
    canvas->login(user_bl);
    updateCanvasesList();
}

void MainWindow::updateCanvasesList()
{
    try
    {
        vector<pair<int, string>> vec = canvas->updateCanvasesList();
        ui->my_canvases_listWidget->clear();
        for (auto &elem : vec)
        {
            //ui->my_canvases_listWidget->addItem(QString::fromStdString(elem.second));
            QListWidgetItem* new_item = new QListWidgetItem(QString::fromStdString(elem.second));
            new_item->setStatusTip(QString::number(elem.first));
            ui->my_canvases_listWidget->addItem(new_item);
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

void MainWindow::on_gen_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed on generate new landscape button";
        canvas->generateNewLandscape(ui->size_value_label->text().toInt());
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

void MainWindow::on_clean_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed on clean button";
        canvas->cleanQImage();
        canvas->resetHeightsMap();
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


void MainWindow::on_size_up_btn_released()
{
    try
    {
        qInfo(logUserAction()) << "Pressed on size up button";
        QString text = ui->size_value_label->text();
        int n = text.toInt();
        if (n < 1025)
        {
            n = (n - 1)*2+1;
            text = QString::number(n);
            ui->size_value_label->setText(text);
            ui->scale_doubleSpinBox->setValue(512./(n-1));
            ui->range_doubleSpinBox->setValue((n-1)*0.75);
            //ui->level_spinBox->setValue((n-1));
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


void MainWindow::on_size_down_btn_released()
{
    try
    {
        qInfo(logUserAction()) << "Pressed on size down button";
        QString text = ui->size_value_label->text();
        int n = text.toInt();
        if (n > 3)
        {
            n = (n - 1)/2+1;
            text = QString::number(n);
            ui->size_value_label->setText(text);
            ui->scale_doubleSpinBox->setValue(512./(n-1));
            ui->range_doubleSpinBox->setValue((n-1)*0.75);
            //ui->level_spinBox->setValue((n-1));
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


void MainWindow::on_draw_variant_comboBox_activated(int index)
{
    try
    {
        qInfo(logUserAction()) << "Changed draw variant comboBox value";
        switch (index)
        {
        case 0:
            canvas->setDrawAlg(CARCAS);
            break;
        case 1:
            canvas->setDrawAlg(TRIANGULAR);
            break;
        case 2:
            canvas->setDrawAlg(ZBUFFER_PARAM);
            break;
        case 3:
            canvas->setDrawAlg(ZBUFFER_INTERPOLATION);
            break;
        case 4:
            canvas->setDrawAlg(ZBUFFER_PARAM_THREADS);
            break;
        default:
            QMessageBox::information(this, "Error", "No such DrawAlg");
            ui->draw_variant_comboBox->setCurrentIndex(0);
            break;
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

void MainWindow::on_mult_spinBox_valueChanged(int arg1)
{
    try
    {
        qInfo(logUserAction()) << "Changed mult spinBox value";
        canvas->setMult(arg1);
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

void MainWindow::on_scale_doubleSpinBox_valueChanged(double arg1)
{
    try
    {
        qInfo(logUserAction()) << "Changed mult spinBox value";
        canvas->setScale(arg1);
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


void MainWindow::on_move_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed move button";
        bool isDouble;

        double dX = ui->move_x->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double dY = ui->move_y->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double dZ = ui->move_z->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        //canvas->transform(Point(dX, dY, dZ), Point(1, 1, 1), Point(0, 0, 0));
        canvas->move(Point(dX, dY, dZ));

        canvas->draw();
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


void MainWindow::on_scale_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed scale button";
        bool isDouble;

        double kX = ui->scale_x->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double kY = ui->scale_y->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double kZ = ui->scale_z->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        //canvas->transform(Point(0, 0, 0), Point(kX, kY, kZ), Point(0, 0, 0));
        canvas->scale(Point(kX, kY, kZ));

        canvas->draw();
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


void MainWindow::on_rotate_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed rotate button";
        bool isDouble;

        double oX = ui->angle_x->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double oY = ui->angle_y->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double oZ = ui->angle_z->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        //canvas->transform(Point(0, 0, 0), Point(1, 1, 1), Point(oX, oY, oZ));
        canvas->rotate(Point(oX, oY, oZ));

        canvas->draw();
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

void MainWindow::on_range_doubleSpinBox_valueChanged(double arg1)
{
    try
    {
        qInfo(logUserAction()) << "Changed range doubleSpinBox value";
        canvas->setRange(arg1);
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

void MainWindow::on_resolution_comboBox_currentTextChanged(const QString &arg1)
{
    try
    {
        qInfo(logUserAction()) << "Changed resolution comboBox value";
        qsizetype n = arg1.indexOf('x');

        QString width = "";
        for (int i = 0; i < n; i++)
        {
            width += arg1[i];
        }

        QString height = "";
        int str_size = arg1.size();
        for (int i = n+1; i < str_size; i++)
        {
            height += arg1[i];
        }
        int w = width.toInt();
        int h = height.toInt();

        canvas->setWidth(w);
        canvas->setHeight(h);
        canvas->updateResolution();
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


void MainWindow::on_pushButton_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed choose color button";
        QColor color = QColorDialog::getColor(canvas->getColor());
        if (color.isValid())
        {
            canvas->setLandscapeColor(color.red(), color.green(), color.blue());
            QString str = QString("background-color: rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
            ui->color_label->setStyleSheet(str);
        }
        else
        {
            QMessageBox::information(this, "Error", "Color is not valid");
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


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    try
    {
        qInfo(logUserAction()) << "Pressed smoothing checkBox";
        canvas->setSmoothing(bool(arg1));
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


void MainWindow::on_read_file_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed read file button";
        string file_name = ui->file_name_lineEdit->text().toStdString();

        canvas->readFromFile(file_name);
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


void MainWindow::on_write_file_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed write file button";
        string file_name = ui->file_name_lineEdit_2->text().toStdString();

        canvas->writeToFile(file_name);
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

void MainWindow::on_load_canvas_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed load canvas button";
        //CanvasBL cbl("hm.txt", "tpa.txt", "color.txt");
        //int r, g, b;
        //cbl.getColor(r, g, b);
        //canvas->selectCanvas(make_shared<LandscapeCanvas>(cbl.getHeightsMap(), cbl.getHeightsMapPoints(), r, g, b));
        QList list = ui->my_canvases_listWidget->selectedItems();
        if (list.size()>0)
        {
            shared_ptr<ParamsBL> params_bl = canvas->selectCanvas(list[0]->statusTip().toInt());

            QString res_str = QString::number(params_bl->getWidth()) + "x" + QString::number(params_bl->getHeight());
            if (ui->resolution_comboBox->findText(res_str) != -1)
                ui->resolution_comboBox->setCurrentIndex(ui->resolution_comboBox->findText(res_str));
            else
            {
                ui->resolution_comboBox->addItem(res_str);
                ui->resolution_comboBox->setCurrentIndex(ui->resolution_comboBox->count()-1);
            }

            ui->range_doubleSpinBox->setValue(params_bl->getRange());

            if (params_bl->getSmooth())
                ui->checkBox->setCheckState(Qt::Checked);
            else
                ui->checkBox->setCheckState(Qt::Unchecked);

            ui->mult_spinBox->setValue(params_bl->getMult());

            QString color_str = QString("background-color: rgb(%1, %2, %3)").arg(params_bl->getRed()).arg(params_bl->getGreen()).arg(params_bl->getBlue());
            ui->color_label->setStyleSheet(color_str);

            ui->size_value_label->setText(QString::number(params_bl->getSize()));

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


void MainWindow::on_write_file_btn_2_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed send canvas to DataBase button";
        //canvas->writeToFile("hm.txt");
        //canvas->getHeightsMapPoints()->writeToFile("tpa.txt");
        //canvas->getLandscapeCanvas()->writeColorToFile("color.txt");

        double range = ui->range_doubleSpinBox->value();
        bool smooth = false;
        if (ui->checkBox->isChecked())
            smooth = true;
        string name = ui->canvas_lineEdit->text().toStdString();

        canvas->createCanvas(range, smooth, name);
        updateCanvasesList();
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


void MainWindow::on_delete_canvas_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed delete canvas button";
        QList list = ui->my_canvases_listWidget->selectedItems();
        for (auto &elem : list)
        {
            canvas->deleteCanvas(elem->statusTip().toInt());
        }
        updateCanvasesList();
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


void MainWindow::on_update_canvas_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed update canvas button";
        QList list = ui->my_canvases_listWidget->selectedItems();
        for (auto &elem : list)
        {
            canvas->updateCanvas(elem->statusTip().toInt());
        }
        updateCanvasesList();
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


void MainWindow::on_write_file_btn_3_clicked()
{
    qInfo(logUserAction()) << "Pressed OpenUnitTestsWindow button";
    unit_tests_window->show();
}

void MainWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button";
    this->hide();
    canvas->logout();
    emit exit();
}


void MainWindow::on_test_user_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed TEST USER button";
        string str;
        canvas->testUser(str);
        QMessageBox::information(this, "Result", QString::fromStdString(str));
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


void MainWindow::on_delete_user_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed DELETE THIS USER button";
        canvas->deleteUser();
        this->hide();
        canvas->logout();
        emit exit();
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

