#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "BaseController.h"
#include "../LandscapeCanvas/LandscapeCanvas.h"

class UserController: public BaseController
{
public:
    UserController();
    UserController(shared_ptr<UserBL> u);

    //void createCanvas(); //No need? It should be in CanvasRepository
    //void deleteCanvas();

    void selectCanvas(shared_ptr<LandscapeCanvas> c);

    void generateNewLandscape(int size);
    void readFromFile(string file_name);
    void writeToFile(string file_name);
    //void drawLandscape();
    shared_ptr<FrameBuffer> getFrameBuffer();
    void cleanCanvas();
    void resetHeightsMap();
    void updateResolution();

    //Resolution setters
    void setWidth(int new_width);
    void setHeight(int new_height);

    //generating seters
    void setRange(float new_range);
    void setSmoothing(bool new_smoothing);

    //drawing seters
    void setMult(int new_mult);
    void setLandscapeColor(int r, int g, int b);

    //transforming
    void transform(const Point& move, const Point& scale, const Point& rotate);
    void move(const Point& move);
    void scale(const Point& scale);
    void rotate(const Point& rotate);

    void getColor(int& r, int& g, int& b) const;

    shared_ptr<LandscapeCanvas> getLandscapeCanvas() const;
    shared_ptr<HeightsMap> getHeightsMap() const;
    shared_ptr<HeightsMapPoints> getHeightsMapPoints() const;
    shared_ptr<TriPolArray> getTriPolArray() const;
    shared_ptr<ZBufferAlg> getZBufferAlg() const;
    int getMult() const;
    int getImgWidth() const;
    int getImgHeight() const;

private:
    shared_ptr<LandscapeCanvas> canvas;
};

#endif // USERCONTROLLER_H
