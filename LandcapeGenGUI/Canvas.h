#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QImage>

#include <memory>
#include <iostream>

using namespace std;

#include "Controllers/usercontroller.h"
#include "Repositorys/CanvasRepository.h"
#include "Repositorys/UsersRepository.h"

enum DrawAlg
{
    CARCAS,
    TRIANGULAR,
    ZBUFFER_PARAM,
    ZBUFFER_INTERPOLATION,
    ZBUFFER_PARAM_THREADS
};

class Canvas : public QWidget
{
public:
    //explicit Canvas(QWidget *parent = nullptr);
    Canvas(shared_ptr<CanvasRepository> canvas_rep, shared_ptr<UsersRepository> users_rep, QWidget *parent = nullptr);
    ~Canvas();

    void createCanvas();
    void deleteCanvas(int id);
    void selectCanvas(int id);
    void updateCanvas(int id);

    void generateNewLandscape(int size);
    void readFromFile(string file_name);
    void writeToFile(string file_name);
    void draw();
    void cleanQImage();
    void resetHeightsMap();
    void updateResolution();

    //Resolution setters
    void setWidth(int new_width);
    void setHeight(int new_height);

    //generating seters
    void setScale(double new_scale);
    void setRange(float new_range);
    void setSmoothing(bool new_smoothing);

    //drawing seters
    void setDrawAlg(DrawAlg alg);
    void setMult(int new_mult);
    void setLandscapeColor(int r, int g, int b);

    //transforming
    void transform(const Point& move, const Point& scale, const Point& rotate);
    void move(const Point& move);
    void scale(const Point& scale);
    void rotate(const Point& rotate);

    QColor getColor() const;
    int getMult() const;
    shared_ptr<HeightsMapPoints> getHeightsMapPoints() const;
    shared_ptr<TriPolArray> getTriPolArray() const;
    shared_ptr<LandscapeCanvas> getLandscapeCanvas() const;

    void setThreadsNumber(int n);

    void testUser(string &str);

    void deleteUser();

    vector<pair<int, string> > updateCanvasesList();

    //BaseController methods
    void login(shared_ptr<UserBL> user_bl);
    void logout();
    shared_ptr<UserBL> getUser();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);

private:
    //Resolution parametres
    int img_width = 720;
    int img_height = 405;

    //drawing parametres
    DrawAlg draw_alg = ZBUFFER_PARAM;//CARCAS;
    int threads_number = 1;

    unique_ptr<QImage> my_img = nullptr;

    bool LMB_is_pressed = false;
    bool RMB_is_pressed = false;
    int previous_x = 0, previous_y = 0;

    unique_ptr<UserController> user_controller;
    shared_ptr<CanvasRepository> canvas_repository;
    shared_ptr<UsersRepository> users_repository;

    shared_ptr<HeightsMapPoints> heights_map_points;

    shared_ptr<TriPolArray> tri_pol_mas;
    shared_ptr<ZBufferAlg> zbuffer_alg;
    shared_ptr<FrameBuffer> frame_buffer;

private:
    int sign(double val);
    void plotImg(int x, int y, QColor c);
    void plotXImg(int x, int y, QColor c, int m = 1);
    void drawImageFT(int i0, int i1);
    void DrawLineBrezenheimFloat(const Point &p1, const Point &p2, QColor c = Qt::black);
    void DrawLineBrezenheimFloat(double X_start, double Y_start, double X_end, double Y_end, QColor c = Qt::black);

    void drawLandScape();
    void carcasDraw();
    void triangularDraw();
    void zbufferParamDraw();
    void zbufferParamDrawWithThreads();
    void zbufferInterpolationDraw();
};

#endif // CANVAS_H
