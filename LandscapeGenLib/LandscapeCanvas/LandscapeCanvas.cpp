#include "LandscapeCanvas.h"

LandscapeCanvas::LandscapeCanvas()
{
    img_width = 960; //1280; //720;
    img_height = 540; //720; //405;

    //painter = make_unique<QPainter>(this);

    resetHeightsMap();

    range = 24.75;
    smoothing = false;

    mult = 1;

    red = 20;
    green = 150;
    blue = 20;

    //frame_buffer.reset();
}

LandscapeCanvas::LandscapeCanvas(HeightsMap &hm)
{
    img_width = 960; //1280; //720;
    img_height = 540; //720; //405;

    //painter = make_unique<QPainter>(this);

    resetHeightsMap(hm);

    range = 24.75;
    smoothing = false;

    mult = 1;

    red = 20;
    green = 150;
    blue = 20;

    //frame_buffer.reset();
}

LandscapeCanvas::LandscapeCanvas(HeightsMap &hm, HeightsMapPoints &hmp, int r, int g, int b)
{
    img_width = 960; //1280; //720;
    img_height = 540; //720; //405;

    //painter = make_unique<QPainter>(this);

    resetHeightsMap();

    range = 24.75;
    smoothing = false;

    mult = 1;

    red = r;
    green = g;
    blue = b;

    //frame_buffer.reset();

    heights_map = make_unique<HeightsMap>(hm);
    heights_map_points = make_shared<HeightsMapPoints>(hmp);
    tri_pol_mas = heights_map_points->createTriPolArray(red, green, blue);
}

LandscapeCanvas::~LandscapeCanvas()
{
}

bool LandscapeCanvas::operator ==(LandscapeCanvas &an_canvas) const
{
    bool res = false;
    bool f1 = false, f2 = false, f3 = false, f4 = false, f5 = false;

    if (this->img_width == an_canvas.img_width &&
            this->img_height == an_canvas.img_height &&
            abs(this->range - an_canvas.range) <= EPS &&
            this->smoothing == an_canvas.smoothing &&
            this->mult == an_canvas.mult &&
            this->red == an_canvas.red &&
            this->green == an_canvas.green &&
            this->blue == an_canvas.blue)
        f1 = true;

    if ((this->heights_map == an_canvas.heights_map) ||
        (this->heights_map && an_canvas.heights_map && *this->heights_map == *an_canvas.heights_map))
        f2 = true;

    if ((this->heights_map_points == an_canvas.heights_map_points) ||
        (this->heights_map_points && an_canvas.heights_map_points && *this->heights_map_points == *an_canvas.heights_map_points))
        f3 = true;

    if ((this->tri_pol_mas == an_canvas.tri_pol_mas) ||
        (this->tri_pol_mas && an_canvas.tri_pol_mas && *this->tri_pol_mas == *an_canvas.tri_pol_mas))
        f4 = true;

    //shared_ptr<FrameBuffer> frame_buffer = zbuffer_alg->getFrameBuffer();
    if ((this->getFrameBuffer() == an_canvas.getFrameBuffer()) ||
        (this->getFrameBuffer() && an_canvas.getFrameBuffer() && *(this->getFrameBuffer()) == *an_canvas.getFrameBuffer()))
        f5 = true;

    res = f1 && f2 && f3 && f4 && f5;

    /*if (this->img_width != an_canvas.img_width ||
            this->img_height != an_canvas.img_height ||
            abs(this->range - an_canvas.range) > EPS ||
            this->smoothing != an_canvas.smoothing ||
            this->mult != an_canvas.mult ||
            this->red != an_canvas.red ||
            this->green != an_canvas.green ||
            this->blue != an_canvas.blue ||
            (this->heights_map && an_canvas.heights_map && *this->heights_map != *an_canvas.heights_map) ||
            *this->heights_map_points != *an_canvas.heights_map_points ||
            *this->tri_pol_mas != *an_canvas.tri_pol_mas ||
            //this->zbuffer_alg != an_canvas.zbuffer_alg ||
            *this->frame_buffer != *an_canvas.frame_buffer)
        res = false;*/
    return res;
}

bool LandscapeCanvas::operator !=(LandscapeCanvas &an_canvas) const
{
    return !(*this == an_canvas);
}

void LandscapeCanvas::generateNewLandscape(int size)
{
    cleanCanvas();
    heights_map = make_unique<HeightsMap>(size);

    heights_map->diamondSquare(range, smoothing); //DIAMOND SQUARE

    double max_h = heights_map->getMaxHeight();
    double k = min((0.9*img_height)/max_h, ((0.9*img_width)/heights_map->getSize()));
    heights_map_points = heights_map->createPoints(k/MULT, k/MULT, k/MULT);
    max_h *= k/MULT;

    tri_pol_mas = heights_map_points->createTriPolArray(red, green, blue);

    Point c = heights_map_points->getCenter();
    heights_map_points->move(Point(-c.getX() + (img_width/(2*MULT)), -c.getY() + (img_height/(2*MULT)), -c.getZ()));
    heights_map_points->rotate(Point(0, 0, 180));

    zbuffer_alg = make_shared<ZBufferAlg>(img_height/MULT, img_width/MULT); // fix width and height
}

void LandscapeCanvas::readFromFile(string file_name)
{
    cleanCanvas();

    heights_map->readFromFile(file_name);
    double max_h = heights_map->getMaxHeight();
    double k = min((0.9*img_height)/max_h, ((0.9*img_width)/heights_map->getSize()));
    heights_map_points = heights_map->createPoints(k/MULT, k/MULT, k/MULT);
    max_h *= k/MULT;

    tri_pol_mas = heights_map_points->createTriPolArray(red, green, blue);


    Point c = heights_map_points->getCenter();
    //getCenter() IN THE MIDDLE
    //heights_map_points->move(Point(-c.getX() + (img_width/(2*MULT)), -c.getY() + (img_height/(2*MULT)), -c.getZ()));
    //heights_map_points->rotate(Point(0, 0, 180));

    //max_h/2 IN THE MIDDLE
    double min_h = heights_map->getMinHeight() * k/MULT;
    heights_map_points->rotate(Point(0, 0, 180), Point(c.getX(), (max_h/2), c.getZ()));
    heights_map_points->move(Point(-c.getX() + (img_width/(2*MULT)), -(max_h-min_h)/2 + (img_height/(2*MULT)), -c.getZ()));


    zbuffer_alg = make_shared<ZBufferAlg>(img_height/MULT, img_width/MULT); // fix width and height
}

void LandscapeCanvas::writeToFile(string file_name)
{
    heights_map->writeToFile(file_name);
}

shared_ptr<FrameBuffer> LandscapeCanvas::getFrameBuffer() const
{
    return zbuffer_alg->getFrameBuffer();
    //return frame_buffer;
}

void LandscapeCanvas::cleanCanvas()
{
    //zbuffer_alg->getFrameBuffer().reset();
    zbuffer_alg->resetFrameBuffer();
    //frame_buffer.reset();
}

void LandscapeCanvas::resetHeightsMap()
{
    //heights_map = make_unique<HeightsMap>();
    heights_map = make_shared<HeightsMap>();
    heights_map_points = heights_map->createPoints(red, green, blue);
    tri_pol_mas = heights_map_points->createTriPolArray();
    //zbuffer_alg = make_unique<ZBufferAlg>(img_width/MULT, img_height/MULT); //(500, 500);
    zbuffer_alg = make_shared<ZBufferAlg>(img_height/MULT, img_width/MULT); //(500, 500);
}

void LandscapeCanvas::resetHeightsMap(HeightsMap &hm)
{
    //heights_map = make_unique<HeightsMap>();
    heights_map = make_shared<HeightsMap>(hm);
    heights_map_points = heights_map->createPoints(red, green, blue);
    tri_pol_mas = heights_map_points->createTriPolArray();
    //zbuffer_alg = make_unique<ZBufferAlg>(img_width/MULT, img_height/MULT); //(500, 500);
    zbuffer_alg = make_shared<ZBufferAlg>(img_height/MULT, img_width/MULT); //(500, 500);
}

void LandscapeCanvas::updateResolution()
{
    zbuffer_alg = make_shared<ZBufferAlg>(img_height/MULT, img_width/MULT);
    const Point& c = heights_map_points->getCenter();
    heights_map_points->transform(Point(-c.getX() + (img_width/(2*MULT)), -c.getY() + (img_height/(2*MULT)), -c.getZ()), Point(1, 1, 1), Point(0, 0, 0));
}

void LandscapeCanvas::setWidth(int new_width)
{
    img_width = new_width;
}

void LandscapeCanvas::setHeight(int new_height)
{
    img_height = new_height;
}

void LandscapeCanvas::setRange(float new_range)
{
    range = new_range;
}

void LandscapeCanvas::setSmoothing(bool new_smoothing)
{
    smoothing = new_smoothing;
}

void LandscapeCanvas::setMult(int new_mult)
{
    const Point& c = heights_map_points->getCenter();
    move(Point(-c.getX() + (img_width/(2*new_mult)), -c.getY() + (img_height/(2*new_mult)), -c.getZ()));
    scale(Point(double(mult)/new_mult, double(mult)/new_mult, double(mult)/new_mult));
    mult = new_mult;
    zbuffer_alg = make_shared<ZBufferAlg>(img_height/MULT, img_width/MULT);
}

void LandscapeCanvas::setLandscapeColor(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
    tri_pol_mas->setColor(r, g, b);
}

void LandscapeCanvas::transform(const Point &move, const Point &scale, const Point &rotate)
{
    heights_map_points->transform(move, scale, rotate);
}

void LandscapeCanvas::move(const Point &move)
{
    heights_map_points->move(move);
}

void LandscapeCanvas::scale(const Point &scale)
{
    heights_map_points->scale(scale);
}

void LandscapeCanvas::rotate(const Point &rotate)
{
    heights_map_points->rotate(rotate);
}

void LandscapeCanvas::getColor(int &r, int &g, int &b) noexcept
{
    r = red;
    g = green;
    b = blue;
}

shared_ptr<HeightsMap> LandscapeCanvas::getHeightsMap() const
{
    return heights_map;
}

shared_ptr<HeightsMapPoints> LandscapeCanvas::getHeightsMapPoints() const
{
    return heights_map_points;
}

shared_ptr<TriPolArray> LandscapeCanvas::getTriPolArray() const
{
    return tri_pol_mas;
}

shared_ptr<ZBufferAlg> LandscapeCanvas::getZBufferAlg() const
{
    return zbuffer_alg;
}

int LandscapeCanvas::getMult() const
{
    return mult;
}

int LandscapeCanvas::getImgWidth() const
{
    return img_width;
}

int LandscapeCanvas::getImgHeight() const
{
    return img_height;
}

void LandscapeCanvas::writeColorToFile(string file_name)
{
    ofstream file(file_name);
    file << red << " " << green << " " << blue << " ";
    file.close();
}
