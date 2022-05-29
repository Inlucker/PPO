#ifndef MODERATORCANVASESCONTROLLER_H
#define MODERATORCANVASESCONTROLLER_H

#include "BaseController.h"
#include "LandscapeCanvas/LandscapeCanvas.h"

class ModeratorCanvasesController : public BaseController
{
public:
    ModeratorCanvasesController();

    void selectCanvas(shared_ptr<LandscapeCanvas> c);

    shared_ptr<FrameBuffer> getFrameBuffer();
    void cleanCanvas();

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

#endif // MODERATORCANVASESCONTROLLER_H
