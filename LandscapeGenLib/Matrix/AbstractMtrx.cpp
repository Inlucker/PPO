#include "AbstractMtrx.h"
#include <cmath>

using namespace std;

AbstractMtrx::AbstractMtrx()
{
    //constructor
    elems_num = 0;
    width = 0;
    height = 0;
    size = 0;
}

bool AbstractMtrx::isEmpty() const noexcept
{
    return !elems_num;
}

int AbstractMtrx::getSize() const noexcept
{
    return size;
}

int AbstractMtrx::getWidth() const noexcept
{
    return width;
}

int AbstractMtrx::getHeight() const noexcept
{
    return height;
}

int AbstractMtrx::elemsNum() const noexcept
{
    return elems_num;
}

AbstractMtrx::~AbstractMtrx()
{
    //destructor
}
