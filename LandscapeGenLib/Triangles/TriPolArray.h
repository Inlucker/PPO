#ifndef TRIPOLARRAY_H
#define TRIPOLARRAY_H

#include "Array/BaseArray.hpp"

class TriangularPolygon;
class HeightsMapPoints;

class TriPolArray : public BaseArray<TriangularPolygon>
{
public:
    using BaseType = BaseArray<TriangularPolygon>;  //alias, will be useful someday
    TriPolArray();
    explicit TriPolArray(int new_size);
    TriPolArray(int new_size, int new_r, int new_g, int new_b);

    //void updatePoints(HeightsMapPoints &map);
    void update();
    void updateFT(int first, int last);
    void setColor(int new_r, int new_g, int new_b);
    int getR() const;
    int getG() const;
    int getB() const;



private:
    int r;
    int g;
    int b;
};

#endif // TRIPOLARRAY_H
