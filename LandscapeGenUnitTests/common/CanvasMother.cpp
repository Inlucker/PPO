#include "CanvasMother.h"
#include "CanvasBLBuilder.h"
#include "HeightsMapBuilder.h"

shared_ptr<CanvasBL> CanvasMother::withSize(int size)
{
    /*shared_ptr<HeightsMap> heights_map = HeightsMapBuilder().withSize(33)->build();
    shared_ptr<CanvasBL> canvas = CanvasBLBuilder().withHeightsMap(heights_map)->build();*/

    shared_ptr<CanvasBL> canvas = CanvasBLBuilder().withHeightsMap(size)->build();
    return canvas;
}
