#include "BaseWindow.h"
#include "ui_BaseWindow.h"

#include <QMessageBox>

#include "Errors/BaseError.h"
#include "Essensities/UserBL.h"
#include "Settings.h"

//#include <iostream>

//using namespace std;

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    //user_repository = make_shared<UsersRepository>();
#ifdef MYSQL
    setupMySQL();
#endif
    user_repository = make_shared<USER_REP>();
    canvas_repository = make_shared<CANVAS_REP>();

    main_window = make_unique<MainWindow>();
    connect(main_window.get(), SIGNAL(exit()), this, SLOT(resetBaseWindow()));

    moderator_window = make_unique<ModeratorWindow>();
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

void BaseWindow::setupMySQL()
{

    /*qDebug() << "localhost";
    qDebug() << "mysql";
    qDebug() << "root";
    qDebug() << "mysql";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mysql");
    db.setUserName("root");
    db.setPassword("mysql");
    if(db.open()){
        qDebug() <<"Connected!";
    }else{
        qDebug() <<"Disconnected!";
    }*/

    db = make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QMYSQL"));

    QString m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString();
    int m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    QString m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString();
    QString m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString();
    QString m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString();

    qDebug() << m_dbhost;
    qDebug() << m_dbport;
    qDebug() << m_dbname;
    qDebug() << m_dbuser;
    qDebug() << m_dbpass;

    db->setHostName(m_dbhost);
    db->setPort(m_dbport);
    db->setDatabaseName(m_dbname);
    db->setUserName(m_dbuser);
    db->setPassword(m_dbpass);

    if(db->open())
    {
        //qDebug() << "Connected!!";
        QSqlQuery query;
        query.exec("SELECT * FROM PPO.Users;");
        while (query.next())
            qDebug() << query.value(0) << query.value(1);
    }
    else
    {
        //qDebug() << "Disconnected!";
    }
}

