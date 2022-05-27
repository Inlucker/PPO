#include "TriPolArray.h"

#include "TriangularPolygon.h"
#include "HeightsMap/HeightsMapPoints.h"

//#include <thread>

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

void TriPolArray::update2(int threadsN)
{
    /*int x[threadsN];
    int dx = elems_num/threadsN;
    x[0] = 0;
    for (int i = 1; i < threadsN; i++)
    {
        x[i] = x[i-1] + dx;
    }

    std::thread *th = new std::thread[threadsN];
    for (int i = 0; i < threadsN-1; i++)
    {
        th[i] = std::thread(&TriPolArray::updateFT, this, x[i], x[i+1]);
    }
    th[threadsN-1] = std::thread(&TriPolArray::updateFT, this, x[threadsN-1], elems_num - 1);

    for (int i = 0; i < threadsN; i++)
    {
        th[i].join();
    }
    delete[] th;*/

    /*for (auto& tri_pol : *this)
    {
        std::thread thr(&TriangularPolygon::update, tri_pol);
        thr.join();
    }*/
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
