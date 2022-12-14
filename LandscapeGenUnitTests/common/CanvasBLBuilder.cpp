#include "CanvasBLBuilder.h"
#include "HeightsMapBuilder.h"

shared_ptr<CanvasBL> CanvasBLBuilder::build()
{
    return make_shared<CanvasBL>(m_id, m_user_id, m_name, *m_heights_map, *m_heights_map_points, m_red, m_green, m_blue);
}

CanvasBLBuilder *CanvasBLBuilder::withId(int id)
{
    m_id = id;
    return this;
}

CanvasBLBuilder *CanvasBLBuilder::withUserId(int user_id)
{
    m_user_id = user_id;
    return this;
}

CanvasBLBuilder *CanvasBLBuilder::withName(string name)
{
    m_name = name;
    return this;
}

CanvasBLBuilder *CanvasBLBuilder::withHeightsMap(shared_ptr<HeightsMap> heights_map)
{
    m_heights_map = heights_map;
    m_heights_map_points = m_heights_map->createPoints();
    return this;
}

CanvasBLBuilder *CanvasBLBuilder::withHeightsMap(int size, bool gen)
{
    m_heights_map = HeightsMapBuilder().withSize(size)->withGen(gen)->build();
    m_heights_map_points = m_heights_map->createPoints();
    return this;
}

CanvasBLBuilder *CanvasBLBuilder::withHeightsMapPoints(shared_ptr<HeightsMapPoints> heights_map_points)
{
    m_heights_map_points = heights_map_points;
    return this;
}

CanvasBLBuilder *CanvasBLBuilder::withColor(int r, int g, int b)
{
    m_red = r;
    m_green = g;
    m_blue = b;
    return this;
}
