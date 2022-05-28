#ifndef HEIGHTSMAPPOINTS_H
#define HEIGHTSMAPPOINTS_H

#include "Matrix/BaseMtrx.hpp"

#include <fstream>

#include "Point.h"
#include "HeightsMap.h"

class TriPolArray;

class HeightsMapPoints : public BaseMtrx<shared_ptr<Point>>
{
public:
    using BaseType = BaseMtrx<shared_ptr<Point>>;  //alias, will be useful someday
    HeightsMapPoints();
    HeightsMapPoints(int new_width, int new_height);
    explicit HeightsMapPoints(int new_size);
    explicit HeightsMapPoints(string& hmp);

    shared_ptr<TriPolArray> createTriPolArray();
    shared_ptr<TriPolArray> createTriPolArray(int r, int g, int b);

    //void transform(const Point moveK, const Point scaleK, const Point rotateK, const Point center); //no need?
    void transform(const Point &moveK, const Point &scaleK, const Point &rotateK);
    void move(const Point &moveK);
    void scale(const Point &scaleK);
    void rotate(const Point &rotateK);
    void rotate(const Point &rotateK, const Point &rotate_center);

    const Point& getCenter() const;

    void writeToFile(string file_name);
    void toStr(string& res);

    bool operator ==(HeightsMapPoints& an_mtrx);
    bool operator !=(HeightsMapPoints& an_mtrx);
private:
    void changeSizes(int new_width, int new_height);
    //void alloc_data();
    void updateCenter() noexcept;
    friend shared_ptr<HeightsMapPoints> HeightsMap::createPoints(double kx, double ky, double kz);
    friend ostream& operator <<(ostream& os, const HeightsMapPoints& map);

private:
    Point map_points_center;
};

ostream& operator <<(ostream& os, const HeightsMapPoints& map);

#endif // HEIGHTSMAPPOINTS_H
