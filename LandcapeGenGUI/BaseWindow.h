#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <memory>
#include <QSqlQuery>

using namespace std;

#include "mainwindow.h"
#include "ModeratorWindow.h"
#include "Controllers/BaseController.h"
#include "Repositorys/UsersRepository.h"
//#include "Repositorys/UsersRepositoryMySQL.h"
//#include "Repositorys/CanvasRepositoryMySQL.h"
#include "LoggingCategories.h"

#include "defines.h"

namespace Ui {
class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

private slots:
    void on_login_btn_clicked();

    void resetBaseWindow();

    void on_registrate_btn_clicked();

private:
    void setupMySQL();

private:
    Ui::BaseWindow *ui;

    unique_ptr<MainWindow> main_window;
    unique_ptr<ModeratorWindow> moderator_window;
    //shared_ptr<UsersRepository> user_repository;
    shared_ptr<USER_REP> user_repository;
    shared_ptr<CANVAS_REP> canvas_repository;

    unique_ptr<QSqlDatabase> db;
};

#endif // BASEWINDOW_H
