#include "HeightsMapBuilder.h"
#include "CanvasMother.h"

shared_ptr<HeightsMap> HeightsMapBuilder::build()
{
    shared_ptr<HeightsMap> heights_map = make_shared<HeightsMap>(m_size);
    if (gen_flag)
        heights_map->diamondSquare();
    return heights_map;
}

HeightsMapBuilder *HeightsMapBuilder::withSize(int size)
{
    m_size = size;
    return this;
}

HeightsMapBuilder *HeightsMapBuilder::withGen(bool gen)
{
    gen_flag = gen;
    return this;
}
