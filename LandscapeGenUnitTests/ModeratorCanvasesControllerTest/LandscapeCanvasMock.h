#ifndef LANDSCAPECANVASMOCK_H
#define LANDSCAPECANVASMOCK_H

#include "LandscapeCanvas/LandscapeCanvas.h"
#include <gmock/gmock.h>

class LandscapeCanvasMock : public LandscapeCanvasI
{
public:
    LandscapeCanvasMock();
    ~LandscapeCanvasMock();

    //MOCK_METHOD(bool, operator==, (LandscapeCanvasI& an_canvas), (override));

    MOCK_METHOD(void, generateNewLandscape, (int), (override));
    MOCK_METHOD(void, readFromFile, (string), (override));
    MOCK_METHOD(void, writeToFile, (string), (override));
    MOCK_METHOD(shared_ptr<FrameBuffer>, getFrameBuffer, (), (override));
    MOCK_METHOD(void, cleanCanvas, (), (override));
    MOCK_METHOD(void, resetHeightsMap, (), (override));
    MOCK_METHOD(void, resetHeightsMap, (HeightsMap&), (override));
    MOCK_METHOD(void, updateResolution, (), (override));

    MOCK_METHOD(void, setWidth, (int), (override));
    MOCK_METHOD(void, setHeight, (int), (override));

    MOCK_METHOD(void, setRange, (float), (override));
    MOCK_METHOD(void, setSmoothing, (bool), (override));

    MOCK_METHOD(void, setMult, (int), (override));
    MOCK_METHOD(void, setLandscapeColor, (int, int, int), (override));

    MOCK_METHOD(void, transform, (const Point&, const Point&, const Point&), (override));
    MOCK_METHOD(void, move, (const Point&), (override));
    MOCK_METHOD(void, scale, (const Point&), (override));
    MOCK_METHOD(void, rotate, (const Point&), (override));

    MOCK_METHOD(void, getColor, (int&, int&, int&), (override, noexcept));

    MOCK_METHOD(shared_ptr<HeightsMap>, getHeightsMap, (), (override, const));
    MOCK_METHOD(shared_ptr<HeightsMapPoints>, getHeightsMapPoints, (), (override, const));
    MOCK_METHOD(shared_ptr<TriPolArray>, getTriPolArray, (), (override, const));
    MOCK_METHOD(shared_ptr<ZBufferAlg>, getZBufferAlg, (), (override, const));
    MOCK_METHOD(int, getMult, (), (override, const));
    MOCK_METHOD(int, getImgWidth, (), (override, const));
    MOCK_METHOD(int, getImgHeight, (), (override, const));

    MOCK_METHOD(void, writeColorToFile, (string), (override));
};

#endif // LANDSCAPECANVASMOCK_H
