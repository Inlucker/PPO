#include "ModeratorCanvasesController.h"

ModeratorCanvasesController::ModeratorCanvasesController()
{
    canvas = make_shared<LandscapeCanvas>();
}

void ModeratorCanvasesController::selectCanvas(shared_ptr<LandscapeCanvasI> c)
{
    canvas = c;
}

shared_ptr<FrameBuffer> ModeratorCanvasesController::getFrameBuffer()
{
    return canvas->getFrameBuffer();
}

void ModeratorCanvasesController::cleanCanvas()
{
    canvas->cleanCanvas();
}

void ModeratorCanvasesController::transform(const Point &move, const Point &scale, const Point &rotate)
{
    canvas->transform(move, scale, rotate);
}

void ModeratorCanvasesController::move(const Point &move)
{
    canvas->move(move);
}

void ModeratorCanvasesController::scale(const Point &scale)
{
    canvas->scale(scale);
}

void ModeratorCanvasesController::rotate(const Point &rotate)
{
    canvas->rotate(rotate);
}

void ModeratorCanvasesController::getColor(int &r, int &g, int &b) const
{
    canvas->getColor(r, g, b);
}

shared_ptr<LandscapeCanvasI> ModeratorCanvasesController::getLandscapeCanvas() const
{
    return canvas;
}

shared_ptr<HeightsMap> ModeratorCanvasesController::getHeightsMap() const
{
    return canvas->getHeightsMap();
}

shared_ptr<HeightsMapPoints> ModeratorCanvasesController::getHeightsMapPoints() const
{
    return canvas->getHeightsMapPoints();
}

shared_ptr<TriPolArray> ModeratorCanvasesController::getTriPolArray() const
{
    return canvas->getTriPolArray();
}

shared_ptr<ZBufferAlg> ModeratorCanvasesController::getZBufferAlg() const
{
    return canvas->getZBufferAlg();
}

int ModeratorCanvasesController::getMult() const
{
    return canvas->getMult();
}

int ModeratorCanvasesController::getImgWidth() const
{
    return canvas->getImgWidth();
}

int ModeratorCanvasesController::getImgHeight() const
{
    return canvas->getImgHeight();
}


