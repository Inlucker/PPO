#ifndef LANDSCAPECANVAS_H
#define LANDSCAPECANVAS_H

#include <memory>
#include <iostream>

using namespace std;

#define MULT getMult()

#include "HeightsMap/HeightsMap.h"
#include "HeightsMap/HeightsMapPoints.h"
#include "Triangles/TriPolArray.h"
#include "Triangles/TriangularPolygon.h"
#include "ZBuffer/ZBufferAlg.h"

class LandscapeCanvasI
{
public:
    //explicit LandscapeCanvasI() = default;
    //virtual ~LandscapeCanvasI() = 0;

    virtual void generateNewLandscape(int size) = 0;
    virtual void readFromFile(string file_name) = 0;
    virtual void writeToFile(string file_name) = 0;
    virtual shared_ptr<FrameBuffer> getFrameBuffer() const = 0;
    virtual void cleanCanvas() = 0;
    virtual void resetHeightsMap() = 0;
    virtual void resetHeightsMap(HeightsMap& hm) = 0;
    virtual void updateResolution() = 0;

    //Resolution setters
    virtual void setWidth(int new_width) = 0;
    virtual void setHeight(int new_height) = 0;

    //generating seters
    virtual void setRange(float new_range) = 0;
    virtual void setSmoothing(bool new_smoothing) = 0;

    //drawing seters
    virtual void setMult(int new_mult) = 0;
    virtual void setLandscapeColor(int r, int g, int b) = 0;

    //transforming
    virtual void transform(const Point& move, const Point& scale, const Point& rotate) = 0;
    virtual void move(const Point& move) = 0;
    virtual void scale(const Point& scale) = 0;
    virtual void rotate(const Point& rotate) = 0;

    virtual void getColor(int& r, int& g, int& b) noexcept = 0;

    virtual shared_ptr<HeightsMap> getHeightsMap() const = 0;
    virtual shared_ptr<HeightsMapPoints> getHeightsMapPoints() const = 0;
    virtual shared_ptr<TriPolArray> getTriPolArray() const = 0;
    virtual shared_ptr<ZBufferAlg> getZBufferAlg() const = 0;
    virtual int getMult() const = 0;
    virtual int getImgWidth() const = 0;
    virtual int getImgHeight() const = 0;

    virtual void writeColorToFile(string file_name) = 0;
};

class LandscapeCanvas : public LandscapeCanvasI
{
public:
    LandscapeCanvas();
    explicit LandscapeCanvas(HeightsMap &hm);
    LandscapeCanvas(HeightsMap &hm, HeightsMapPoints &hmp, int r, int g, int b);
    virtual ~LandscapeCanvas();
    bool operator ==(LandscapeCanvas& an_canvas) const;
    bool operator !=(LandscapeCanvas& an_canvas) const;

    void generateNewLandscape(int size);
    void readFromFile(string file_name);
    void writeToFile(string file_name);
    //virtual void drawLandscape() = 0;
    shared_ptr<FrameBuffer> getFrameBuffer() const;
    void cleanCanvas();
    void resetHeightsMap();
    void resetHeightsMap(HeightsMap& hm);
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

    void getColor(int& r, int& g, int& b) noexcept;

    shared_ptr<HeightsMap> getHeightsMap() const;
    shared_ptr<HeightsMapPoints> getHeightsMapPoints() const;
    shared_ptr<TriPolArray> getTriPolArray() const;
    shared_ptr<ZBufferAlg> getZBufferAlg() const;
    int getMult() const;
    int getImgWidth() const;
    int getImgHeight() const;

    void writeColorToFile(string file_name);

private:
    //Resolution parametres
    int img_width = 720;
    int img_height = 405;

    //generating parametres
    float range = 24.75;
    bool smoothing = false;

    //drawing parametres
    int mult = 1;
    int red = 20;
    int green = 150;
    int blue = 20;

    shared_ptr<HeightsMap> heights_map;
    shared_ptr<HeightsMapPoints> heights_map_points;

    shared_ptr<TriPolArray> tri_pol_mas;
    shared_ptr<ZBufferAlg> zbuffer_alg;
    //shared_ptr<FrameBuffer> frame_buffer;
};

#endif // LANDSCAPECANVAS_H
