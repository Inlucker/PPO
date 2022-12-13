#ifndef LANDSCAPECANVASMOCK_H
#define LANDSCAPECANVASMOCK_H

#include "LandscapeCanvas/LandscapeCanvas.h"
#include <gmock/gmock.h>

class LandscapeCanvasMock : public LandscapeCanvasI
{
public:
    LandscapeCanvasMock()
    {
        // By default, all calls are delegated to the real object.
        ON_CALL(*this, generateNewLandscape).WillByDefault([this](int size) { return real_.generateNewLandscape(size); });
        ON_CALL(*this, readFromFile).WillByDefault([this](string file_name) { return real_.readFromFile(file_name); });
        ON_CALL(*this, writeToFile).WillByDefault([this](string file_name) { return real_.writeToFile(file_name); });
        ON_CALL(*this, getFrameBuffer).WillByDefault([this]() { return real_.getFrameBuffer(); });
        ON_CALL(*this, cleanCanvas).WillByDefault([this]() { return real_.cleanCanvas(); });
        //ON_CALL(*this, resetHeightsMap).WillByDefault([this]() { return real_.resetHeightsMap(); });
        //ON_CALL(*this, resetHeightsMap).WillByDefault([this](HeightsMap& hm) { return real_.resetHeightsMap(hm); });
        ON_CALL(*this, updateResolution).WillByDefault([this]() { return real_.updateResolution(); });

        ON_CALL(*this, setWidth).WillByDefault([this](int new_width) { return real_.setWidth(new_width); });
        ON_CALL(*this, setHeight).WillByDefault([this](int new_height) { return real_.setHeight(new_height); });

        ON_CALL(*this, setRange).WillByDefault([this](float new_range) { return real_.setRange(new_range); });
        ON_CALL(*this, setSmoothing).WillByDefault([this](bool new_smoothing) { return real_.setSmoothing(new_smoothing); });

        ON_CALL(*this, setMult).WillByDefault([this](int new_mult) { return real_.setMult(new_mult); });
        ON_CALL(*this, setLandscapeColor).WillByDefault([this](int r, int g, int b) { return real_.setLandscapeColor(r, g, b); });

        ON_CALL(*this, transform).WillByDefault([this](const Point& move, const Point& scale, const Point& rotate)
                                                { return real_.transform(move, scale, rotate); });
        ON_CALL(*this, move).WillByDefault([this](const Point& move) { return real_.move(move); });
        ON_CALL(*this, scale).WillByDefault([this](const Point& scale) { return real_.scale(scale); });
        ON_CALL(*this, rotate).WillByDefault([this](const Point& rotate) { return real_.rotate(rotate); });

        ON_CALL(*this, getColor).WillByDefault([this](int& r, int& g, int& b) { return real_.getColor(r, g, b); });

        ON_CALL(*this, getHeightsMap).WillByDefault([this]() { return real_.getHeightsMap(); });
        ON_CALL(*this, getHeightsMapPoints).WillByDefault([this]() { return real_.getHeightsMapPoints(); });
        ON_CALL(*this, getTriPolArray).WillByDefault([this]() { return real_.getTriPolArray(); });
        ON_CALL(*this, getZBufferAlg).WillByDefault([this]() { return real_.getZBufferAlg(); });
        ON_CALL(*this, getMult).WillByDefault([this]() { return real_.getMult(); });
        ON_CALL(*this, getImgWidth).WillByDefault([this]() { return real_.getImgWidth(); });
        ON_CALL(*this, getImgHeight).WillByDefault([this]() { return real_.getImgHeight(); });

        ON_CALL(*this, writeColorToFile).WillByDefault([this](string file_name) { return real_.writeColorToFile(file_name); });
    }

    //LandscapeCanvasMock();
    ~LandscapeCanvasMock();

    //MOCK_METHOD(bool, operator==, (LandscapeCanvasI& an_canvas), (override));

    MOCK_METHOD(void, generateNewLandscape, (int), (override));
    MOCK_METHOD(void, readFromFile, (string), (override));
    MOCK_METHOD(void, writeToFile, (string), (override));
    MOCK_METHOD(shared_ptr<FrameBuffer>, getFrameBuffer, (), (override, const));
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


private:
    LandscapeCanvas real_;
};

#endif // LANDSCAPECANVASMOCK_H
