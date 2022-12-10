#include "UnitTestsWindow.h"
#include "ui_UnitTestsWindow.h"

#include <QMessageBox>

UnitTestsWindow::UnitTestsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitTestsWindow)
{
    ui->setupUi(this);

    ui->user_controller_test_btn->hide();
}

UnitTestsWindow::~UnitTestsWindow()
{
    delete ui;
}

void UnitTestsWindow::on_user_controller_test_btn_clicked()
{
    try
    {
        UserControllerTest uct;
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


void UnitTestsWindow::on_base_controller_test_btn_clicked()
{
    try
    {
        BaseControllerTest bct;
        const string& out = bct.getOutput();
        //ui->textEdit->clear();
        //ui->textEdit->append(QString(out.c_str()));
        ui->textEdit->setPlainText(QString(out.c_str()));
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


void UnitTestsWindow::on_canvas_repository_test_btn_clicked()
{
    try
    {
        CanvasRepositoryTest crt;
        const string& out = crt.getOutput();
        ui->textEdit->setPlainText(QString(out.c_str()));
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

