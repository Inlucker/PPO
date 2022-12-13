#ifndef MODERATORCANVASWINDOW_H
#define MODERATORCANVASWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>

#include "Controllers/ModeratorCanvasesController.h"
#include "Repositorys/CanvasRepository.h"
//#include "Repositorys/CanvasRepositoryMySQL.h"
#include "Repositorys/UsersRepository.h"
//#include "Repositorys/UsersRepositoryMySQL.h"
#include "defines.h"

#include <memory>

using namespace std;

namespace Ui {
class ModeratorCanvasWindow;
}

class ModeratorCanvasWindow : public QWidget
{
    Q_OBJECT

public:
    ModeratorCanvasWindow(int u_id = -1, QWidget *parent = nullptr);
    ~ModeratorCanvasWindow();

    void setId(int id);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);

signals:
    void exit();

private slots:
    void on_exit_btn_clicked();

    void on_load_btn_clicked();

    void on_load_btn_2_clicked();

private:
    void updateList();
    void plotXImg(int x, int y, QColor c, int m = 1);
    void drawLandScape();
    void cleanQImage();

private:
    Ui::ModeratorCanvasWindow *ui;
    int user_id = -1;

    int img_width = 720;
    int img_height = 405;

    unique_ptr<QImage> my_img = nullptr;

    bool LMB_is_pressed = false;
    bool RMB_is_pressed = false;
    int previous_x = 0, previous_y = 0;

    unique_ptr<ModeratorCanvasesController> controller;
    shared_ptr<CANVAS_REP> canvas_repository;
    shared_ptr<USER_REP> users_repository;

    //unique_ptr<QWidget> canvas;
};

#endif // MODERATORCANVASWINDOW_H
