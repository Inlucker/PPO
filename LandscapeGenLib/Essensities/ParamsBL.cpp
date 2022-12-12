#include "ParamsBL.h"
#include "Matrix/BaseMtrx.h"

ParamsBL::ParamsBL(int c_id, int w, int h, double ran, bool s, int m, int r, int g, int b, int siz) :
    canvas_id(c_id), width(w), height(h), range(ran), mult(m), red(r), green(g), blue(b), size(siz), smooth(s)
{

}

bool ParamsBL::operator ==(ParamsBL &an_p)
{
    bool res = true;

    if (this->canvas_id != an_p.canvas_id ||
            this->width != an_p.width ||
            this->height != an_p.height ||
            abs(this->range - an_p.range) > EPS ||
            this->smooth != an_p.smooth ||
            this->mult != an_p.mult ||
            this->red != an_p.red ||
            this->green != an_p.green ||
            this->blue != an_p.blue ||
            this->size != an_p.size)
        res = false;
    return res;
}

bool ParamsBL::operator !=(ParamsBL &an_p)
{
    return !(*this == an_p);
}

int ParamsBL::getCanvasID() noexcept
{
    return canvas_id;
}

int ParamsBL::getWidth() noexcept
{
    return width;
}

int ParamsBL::getHeight() noexcept
{
    return height;
}

double ParamsBL::getRange() noexcept
{
    return range;
}

bool ParamsBL::getSmooth() noexcept
{
    return smooth;
}

int ParamsBL::getMult() noexcept
{
    return mult;
}

int ParamsBL::getRed() noexcept
{
    return red;
}

int ParamsBL::getGreen() noexcept
{
    return green;
}

int ParamsBL::getBlue() noexcept
{
    return blue;
}

int ParamsBL::getSize() noexcept
{
    return size;
}
