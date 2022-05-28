#include "BaseWindow.h"
#include "ui_BaseWindow.h"

#include <QMessageBox>

#include "Errors/BaseError.h"
#include "Essensities/UserBL.h"
#include "Settings.h"

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    user_repository = make_shared<UsersRepository>();
    canvas_repository = make_shared<CanvasRepository>();

    main_window = make_unique<MainWindow>(canvas_repository, user_repository);
    connect(main_window.get(), SIGNAL(exit()), this, SLOT(resetBaseWindow()));

    moderator_window = make_unique<ModeratorWindow>(canvas_repository, user_repository);
    connect(moderator_window.get(), SIGNAL(exit()), this, SLOT(resetBaseWindow()));
}

BaseWindow::~BaseWindow()
{
    delete ui;
}

void BaseWindow::on_login_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed on login button";
        string login = ui->login_lineEdit->text().toStdString();
        string password = ui->password_lineEdit->text().toStdString();
        shared_ptr<UserBL> user_bl = user_repository->getUser(login, password);
        if (user_bl->getRole() == "canvas_user")
        {
            main_window->login(user_bl);
            main_window->show();
            this->hide();
        }
        else if (user_bl->getRole() == "moderator")
        {
            moderator_window->login(user_bl);
            moderator_window->show();
            this->hide();
        }
        else
        {
            QMessageBox::information(this, "Error", "No such role");
        }
        qInfo(logUserAction()) << "Login completed";
    }
    catch (BaseError &er)
    {
        resetBaseWindow();
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}

void BaseWindow::resetBaseWindow()
{
    this->show();
    //canvas_repository->setRole("guest", "guest");
    //user_repository->setRole("guest", "guest");
    Settings::set(Settings::DBUser, Settings::DataBase) = "guest";
    Settings::set(Settings::DBPass, Settings::DataBase) = "guest";
}


void BaseWindow::on_registrate_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed on registrate button";
        string login = ui->login_lineEdit->text().toStdString();
        string password = ui->password_lineEdit->text().toStdString();
        string role = ui->role_comboBox->currentText().toStdString();
        UserBL user_bl(0, login, password, role, 0);
        user_repository->addUser(user_bl);
        QMessageBox::information(this, "Error", "Registration completed");
        qInfo(logUserAction()) << "Registration completed";
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

