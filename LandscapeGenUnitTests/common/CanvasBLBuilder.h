#ifndef CANVASBLBUILDER_H
#define CANVASBLBUILDER_H

//#include "../LandscapeGenLib/Essensities/CanvasBL.h"
#include "Essensities/CanvasBL.h"

class CanvasBLBuilder
{
public:
    CanvasBLBuilder() = default;

    shared_ptr<CanvasBL> build();
    CanvasBLBuilder* withId(int id);
    CanvasBLBuilder* withUserId(int user_id);
    CanvasBLBuilder* withName(string name);
    CanvasBLBuilder* withHeightsMap(shared_ptr<HeightsMap> heights_map);
    CanvasBLBuilder* withHeightsMap(int size, bool gen = true);
    CanvasBLBuilder* withHeightsMapPoints(shared_ptr<HeightsMapPoints> heights_map_points);
    CanvasBLBuilder* withColor(int r, int g, int b);

private:
    int m_id = 1;
    int m_user_id = 1;
    string m_name = "CanvasName";
    shared_ptr<HeightsMap> m_heights_map = make_shared<HeightsMap>();
    shared_ptr<HeightsMapPoints> m_heights_map_points = make_shared<HeightsMapPoints>();
    int m_red = 20, m_green = 150, m_blue = 20;
};

#endif // CANVASBLBUILDER_H
