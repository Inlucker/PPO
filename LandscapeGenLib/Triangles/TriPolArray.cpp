#include "TriPolArray.h"

#include "TriangularPolygon.h"
#include "HeightsMap/HeightsMapPoints.h"

using namespace std;

TriPolArray::TriPolArray()
{
    r = 128;
    g = 128;
    b = 128;
}

TriPolArray::TriPolArray(int new_size) : BaseType(new_size)
{
    r = 128;
    g = 128;
    b = 128;
}

TriPolArray::TriPolArray(int new_size, int new_r, int new_g, int new_b) : BaseType(new_size)
{
    r = new_r;
    g = new_g;
    b = new_b;
}

void TriPolArray::update()
{
    for (auto& tri_pol : *this)
        tri_pol.update();
}

void TriPolArray::updateFT(int first, int last)
{
    for (int i = first; i <= last; i++)
    {
        (*this)[i].update();
    }
}

void TriPolArray::setColor(int new_r, int new_g, int new_b)
{
    r = new_r;
    g = new_g;
    b = new_b;
}

int TriPolArray::getR() const
{
    return r;
}

int TriPolArray::getG() const
{
    return g;
}

int TriPolArray::getB() const
{
    return b;
}

/*void TriPolArray::updatePoints(HeightsMapPoints &map)
{
    Iterator<TriangularPolygon> mas_it = this->begin();
    for (int i = 0; i < (map.getSize()-1); i++)
    {
        for (int j = 0; j < (map.getSize()-1); j++)
        {
            if ((j+i) % 2 == 1)
            {
                mas_it->setPoints(map(i, j), map(i, j+1), map(i+1, j));
                mas_it++;
                mas_it->setPoints(map(i+1, j), map(i, j+1), map(i+1, j+1));
                mas_it++;
            }
            else
            {
                mas_it->setPoints(map(i, j), map(i+1, j+1), map(i, j+1));
                mas_it++;
                mas_it->setPoints(map(i, j), map(i+1, j), map(i+1, j+1));
                mas_it++;
            }
        }
    }
}*/
