#ifndef CANVASBL_H
#define CANVASBL_H

#include<fstream>

#include "HeightsMap/HeightsMap.h"
#include "HeightsMap/HeightsMapPoints.h"
#include "Triangles/TriangularPolygon.h"
#include "Triangles/TriPolArray.h"

class CanvasBL
{
public:
    CanvasBL() = delete;
    //CanvasBL(string fn1, string fn2, string fn3);
    CanvasBL(int _id, int u_id, string n, string& hm, string& tpa, string& c);
    CanvasBL(int _id, int u_id, string n, HeightsMap& hm, HeightsMapPoints& hmp, int r, int g, int b);

    bool operator ==(CanvasBL& an_c) const;
    bool operator !=(CanvasBL& an_c) const;

    int getId();
    int getUserId();
    string getName();
    HeightsMap& getHeightsMap();
    HeightsMapPoints& getHeightsMapPoints();
    void getColor(int& r, int& g, int& b) noexcept;
    void getColor(string& c) noexcept;
private:
    string strFromFile(string file_name);

private:
    int id;
    int user_id;
    string name;
    HeightsMap heights_map;
    HeightsMapPoints heights_map_points;
    int red, green, blue;

};

#endif // CANVASBL_H
