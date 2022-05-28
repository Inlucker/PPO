#include "usercontroller.h"
#include "Essensities/CanvasBL.h"

UserController::UserController()
{
    canvas = make_shared<LandscapeCanvas>();
}

UserController::UserController(shared_ptr<UserBL> u) : BaseController(u)
{
    canvas = make_shared<LandscapeCanvas>();
}

void UserController::selectCanvas(shared_ptr<LandscapeCanvas> c)
{
    //cout << "lol1" << endl;
    canvas = c;
    //cout << "lol2" << endl;
}

void UserController::generateNewLandscape(int size)
{
    canvas->generateNewLandscape(size);
}

void UserController::readFromFile(string file_name)
{
    canvas->readFromFile(file_name);
}

void UserController::writeToFile(string file_name)
{
    canvas->writeToFile(file_name);
}

shared_ptr<FrameBuffer> UserController::getFrameBuffer()
{
    return canvas->getFrameBuffer();
}

void UserController::cleanCanvas()
{
    canvas->cleanCanvas();
}

void UserController::resetHeightsMap()
{
    canvas->resetHeightsMap();
}

void UserController::updateResolution()
{
    canvas->updateResolution();
}

void UserController::setWidth(int new_width)
{
    canvas->setWidth(new_width);
}

void UserController::setHeight(int new_height)
{
    canvas->setHeight(new_height);
}

void UserController::setRange(float new_range)
{
    canvas->setRange(new_range);
}

void UserController::setSmoothing(bool new_smoothing)
{
    canvas->setSmoothing(new_smoothing);
}

void UserController::setMult(int new_mult)
{
    canvas->setMult(new_mult);
}

void UserController::setLandscapeColor(int r, int g, int b)
{
    canvas->setLandscapeColor(r, g, b);
}

void UserController::transform(const Point &move, const Point &scale, const Point &rotate)
{
    canvas->transform(move, scale, rotate);
}

void UserController::move(const Point &move)
{
    canvas->move(move);
}

void UserController::scale(const Point &scale)
{
    canvas->scale(scale);
}

void UserController::rotate(const Point &rotate)
{
    canvas->rotate(rotate);
}

void UserController::getColor(int &r, int &g, int &b) const
{
    canvas->getColor(r, g, b);
}

shared_ptr<LandscapeCanvas> UserController::getLandscapeCanvas() const
{
    return canvas;
}

shared_ptr<HeightsMap> UserController::getHeightsMap() const
{
    return canvas->getHeightsMap();
}

shared_ptr<HeightsMapPoints> UserController::getHeightsMapPoints() const
{
    return canvas->getHeightsMapPoints();
}

shared_ptr<TriPolArray> UserController::getTriPolArray() const
{
    return canvas->getTriPolArray();
}

shared_ptr<ZBufferAlg> UserController::getZBufferAlg() const
{
    return canvas->getZBufferAlg();
}

int UserController::getMult() const
{
    return canvas->getMult();
}

int UserController::getImgWidth() const
{
    return canvas->getImgWidth();
}

int UserController::getImgHeight() const
{
    return canvas->getImgHeight();
}


