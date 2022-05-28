#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <memory>

using namespace std;

#include "mainwindow.h"
#include "ModeratorWindow.h"
#include "Controllers/BaseController.h"
#include "Repositorys/UsersRepository.h"
#include "LoggingCategories.h"

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
    Ui::BaseWindow *ui;

    unique_ptr<MainWindow> main_window;
    unique_ptr<ModeratorWindow> moderator_window;
    shared_ptr<UsersRepository> user_repository;
    shared_ptr<CanvasRepository> canvas_repository;
};

#endif // BASEWINDOW_H
