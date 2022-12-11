#include "ParamsBL.h"

ParamsBL::ParamsBL(int c_id, int w, int h, int ran, bool s, int m, int r, int g, int b, int siz) :
    canvas_id(c_id), width(w), height(h), range(ran), mult(m), red(r), green(g), blue(b), size(siz), smooth(s)
{

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

int ParamsBL::getRange() noexcept
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
