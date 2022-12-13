#include <QtTest>

// add necessary includes here
#include "Controllers/usercontroller.h"

class UserControllerTest : public QObject
{
    Q_OBJECT

public:
    UserControllerTest();
    ~UserControllerTest();

private slots:
    void init();

    //void noParamsConstructorTest();
    //void userBLConstructorTest();

    void selectCanvasTest();

    void generateNewLandscapeTest();
    void readFromFileTest();
    void writeToFileTest();
    void getFrameBufferTest();
    void cleanCanvasTest();
    void resetHeightsMapTest();
    void updateResolutionTest();

    void setWidthTest();
    void setHeightTest();

    //void setRangeTest();
    void setSmoothingTest();

    void setMultTest();
    void setLandscapeColorTest();

    void transformTest();
    void moveTest();
    void scaleTest();
    void rotateTest();

    void getColorTest();
    void getLandscapeCanvasTest();
    void getHeightsMapTest();
    void getHeightsMapPointsTest();
    void getTriPolArrayTest();
    void getZBufferAlgTest();
    void getMultTest();
    void getImgWidthTest();
    void getImgHeightTest();

    void cleanup();

private:
    unique_ptr<UserController> sut;
};

UserControllerTest::UserControllerTest()
{

}

UserControllerTest::~UserControllerTest()
{

}

void UserControllerTest::init()
{
    sut = make_unique<UserController>();
}

void UserControllerTest::selectCanvasTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvas> same_canvas = make_shared<LandscapeCanvas>();

    //ACT
    sut->selectCanvas(same_canvas);

    //ASSERT
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();
    QVERIFY2(canvas == same_canvas, "selectCanvasTest error");
}

void UserControllerTest::generateNewLandscapeTest()
{
    //ARRANGE
    int size = 5;

    //ACT
    sut->generateNewLandscape(size);

    //ASSERT
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();
    QVERIFY2(sut->getLandscapeCanvas()->getHeightsMap()->getSize() == size, "generateNewLandscapeTest error");
    QVERIFY2(sut->getLandscapeCanvas()->getHeightsMapPoints()->getSize() == size, "generateNewLandscapeTest error");
    QVERIFY2(sut->getLandscapeCanvas()->getTriPolArray()->size() == 32,
             QString("%1 != %2").arg(QString::number(sut->getLandscapeCanvas()->getTriPolArray()->size()),
                                     QString::number(32)).toStdString().c_str());
}

void UserControllerTest::readFromFileTest()
{
    //ARRANGE
    int size = 5;
    HeightsMap same_heights_map(size);
    same_heights_map.diamondSquare();
    string file_name = "readFromFileTest.txt";
    ofstream file(file_name);
    if (!file)
        QFAIL("file open error");
    file << size << " ";
    file << size << " ";
    for (auto& elem : same_heights_map)
    {
        file << to_string(elem) << " ";
    }
    file.close();

    //ACT
    sut->readFromFile(file_name);

    //ASSERT
    shared_ptr<HeightsMap> heights_map = sut->getLandscapeCanvas()->getHeightsMap();
    QVERIFY2(*heights_map == same_heights_map, "readFromFileTest error");
}

void UserControllerTest::writeToFileTest()
{
    //ARRANGE
    int size = 5;
    sut->generateNewLandscape(size);
    string file_name = "writeToFileTest.txt";

    //ACT
    sut->writeToFile(file_name);

    //ASSERT
    string file_text = "";
    ifstream file(file_name);
    if (!file)
        QFAIL("file open error");
    while (!file.eof())
    {
        string tmp;
        file >> tmp;
        file_text += tmp + " ";
    }
    file.close();

    HeightsMap heights_map = HeightsMap(file_text);
    string s;
    heights_map.toStr(s);
    QString hm1 = QString::fromStdString(s);
    sut->getHeightsMap()->toStr(s);
    QString hm2 = QString::fromStdString(s);

    QVERIFY2(heights_map == *sut->getHeightsMap(),
             QString("%1 != %2").arg(hm1, hm2).toStdString().c_str());
}

void UserControllerTest::getFrameBufferTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvas> same_canvas = make_shared<LandscapeCanvas>();
    sut->selectCanvas(same_canvas);

    //ACT
    shared_ptr<FrameBuffer> frame_buffer = sut->getFrameBuffer();

    //ASSERT
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();
    QVERIFY2(frame_buffer == same_canvas->getFrameBuffer(), "getFrameBufferTest error");
}

void UserControllerTest::cleanCanvasTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvas> same_canvas = sut->getLandscapeCanvas();
    sut->generateNewLandscape(5);
    sut->getZBufferAlg()->execute(*sut->getTriPolArray());
    FrameBuffer same_frame_buff = FrameBuffer(sut->getFrameBuffer()->getWidth(), sut->getFrameBuffer()->getHeight());

    //ACT
    sut->cleanCanvas();

    //ASSERT
    QVERIFY2(*sut->getFrameBuffer() == same_frame_buff, "cleanCanvasTest error");
}

void UserControllerTest::resetHeightsMapTest()
{
    //ARRANGE
    sut->generateNewLandscape(5);
    HeightsMap heights_map_exp = HeightsMap();
    int r, g, b;
    sut->getColor(r, g, b);
    HeightsMapPoints heights_map_points_exp = *heights_map_exp.createPoints(r, g, b);
    TriPolArray tri_pol_mas_exp = *heights_map_points_exp.createTriPolArray();

    //ACT
    sut->resetHeightsMap();

    //ASSERT
    QVERIFY2(*sut->getHeightsMap() == heights_map_exp, "resetHeightsMapTest error");
    QVERIFY2(*sut->getHeightsMapPoints() == heights_map_points_exp, "resetHeightsMapTest error");
    QVERIFY2(*sut->getTriPolArray() == tri_pol_mas_exp, "resetHeightsMapTest error");
}

void UserControllerTest::updateResolutionTest()
{
    //ARRANGE
    int size = 5;
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();
    sut->generateNewLandscape(size);
    HeightsMapPoints heights_map_points_exp = *sut->getHeightsMapPoints();
    double mult = sut->getMult();
    int img_width = 800;
    int img_height = 600;
    const Point& c = heights_map_points_exp.getCenter();
    heights_map_points_exp.transform(Point(-c.getX() + (img_width/(2*mult)), -c.getY() + (img_height/(2*mult)), -c.getZ()), Point(1, 1, 1), Point(0, 0, 0));

    sut->setWidth(img_width);
    sut->setHeight(img_height);

    //ACT
    sut->updateResolution();

    //ASSERT
    QVERIFY2(*sut->getHeightsMapPoints() == heights_map_points_exp, "updateResolutionTest error");
}

void UserControllerTest::setWidthTest()
{
    //ARRANGE
    int width_exp = 500;

    //ACT
    sut->setWidth(width_exp);

    //ASSERT
    int width = sut->getImgWidth();
    QVERIFY2(width == width_exp, "setWidthTest error");
}

void UserControllerTest::setHeightTest()
{
    //ARRANGE
    int height_exp = 400;

    //ACT
    sut->setHeight(height_exp);

    //ASSERT
    int height = sut->getImgHeight();
    QVERIFY2(height == height_exp, "setHeightTest error");
}

/*void UserControllerTest::setRangeTest()
{
    //ARRANGE
    float exp = 200.50;

    //ACT
    sut->setRange(exp);

    //ASSERT
    float res = 200.51;
    if (!qFuzzyCompare(res, exp))
        QFAIL("setRangeTest error");
}*/

void UserControllerTest::setSmoothingTest()
{
    //ARRANGE
    bool exp = true;

    //ACT
    sut->setSmoothing(exp);

    //ASSERT
    bool res = sut->getImgHeight();
    QVERIFY2(res == exp, "setSmoothingTest error");
}

void UserControllerTest::setMultTest()
{
    //ARRANGE
    int exp = 7;

    //ACT
    sut->setMult(exp);

    //ASSERT
    int res = sut->getMult();
    QVERIFY2(res == exp, "setMultTest error");
}

void UserControllerTest::setLandscapeColorTest()
{
    //ARRANGE
    int r_exp = 1, g_exp = 2, b_exp = 3;

    //ACT
    sut->setLandscapeColor(r_exp, g_exp, b_exp);

    //ASSERT
    int r, g, b;
    sut->getColor(r, g, b);
    QVERIFY2(r == r_exp && g == g_exp && b == b_exp, "setLandscapeColorTest error");
}

void UserControllerTest::transformTest()
{
    //ARRANGE
    sut->generateNewLandscape(5);
    HeightsMapPoints hmp_exp = *sut->getHeightsMapPoints();
    Point p1(1, 1, 1), p2(2, 2, 2), p3(3, 3, 3);
    hmp_exp.transform(p1, p2, p3);

    //ACT
    sut->transform(p1, p2, p3);

    //ASSERT
    shared_ptr<HeightsMapPoints> hmp = sut->getHeightsMapPoints();
    QVERIFY2(*hmp == hmp_exp, "transformTest error");
}

void UserControllerTest::moveTest()
{
    //ARRANGE
    sut->generateNewLandscape(5);
    HeightsMapPoints hmp_exp = *sut->getHeightsMapPoints();
    Point p(1, 1, 1);
    hmp_exp.move(p);

    //ACT
    sut->move(p);

    //ASSERT
    shared_ptr<HeightsMapPoints> hmp = sut->getHeightsMapPoints();
    QVERIFY2(*hmp == hmp_exp, "moveTest error");
}

void UserControllerTest::scaleTest()
{
    //ARRANGE
    sut->generateNewLandscape(5);
    HeightsMapPoints hmp_exp = *sut->getHeightsMapPoints();
    Point p(1, 1, 1);
    hmp_exp.scale(p);

    //ACT
    sut->scale(p);

    //ASSERT
    shared_ptr<HeightsMapPoints> hmp = sut->getHeightsMapPoints();
    QVERIFY2(*hmp == hmp_exp, "scaleTest error");
}

void UserControllerTest::rotateTest()
{
    //ARRANGE
    sut->generateNewLandscape(5);
    HeightsMapPoints hmp_exp = *sut->getHeightsMapPoints();
    Point p(1, 1, 1);
    hmp_exp.rotate(p);

    //ACT
    sut->rotate(p);

    //ASSERT
    shared_ptr<HeightsMapPoints> hmp = sut->getHeightsMapPoints();
    QVERIFY2(*hmp == hmp_exp, "rotateTest error");
}

void UserControllerTest::getColorTest()
{
    //ARRANGE
    int r_exp = 1, g_exp = 2, b_exp = 3;
    sut->setLandscapeColor(r_exp, g_exp, b_exp);
    int r, g, b;

    //ACT
    sut->getColor(r, g, b);

    //ASSERT
    QVERIFY2(r == r_exp && g == g_exp && b == b_exp, "getColorTest error");
}

void UserControllerTest::getLandscapeCanvasTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvas> canvas_exp = make_shared<LandscapeCanvas>();
    sut->selectCanvas(canvas_exp);

    //ACT
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();

    //ASSERT
    QVERIFY2(canvas == canvas_exp, "getLandscapeCanvasTest error");
}

void UserControllerTest::getHeightsMapTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();
    canvas->generateNewLandscape(5);
    shared_ptr<HeightsMap> heigths_map_exp = canvas->getHeightsMap();

    //ACT
    shared_ptr<HeightsMap> heights_map = sut->getHeightsMap();

    //ASSERT
    QVERIFY2(heights_map == heigths_map_exp, "getHeightsMapTest error");
}

void UserControllerTest::getHeightsMapPointsTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();
    canvas->generateNewLandscape(5);
    shared_ptr<HeightsMapPoints> heigths_map_points_exp = canvas->getHeightsMapPoints();

    //ACT
    shared_ptr<HeightsMapPoints> heigths_map_point = sut->getHeightsMapPoints();

    //ASSERT
    QVERIFY2(heigths_map_point == heigths_map_points_exp, "getHeightsMapPointsTest error");
}

void UserControllerTest::getTriPolArrayTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();
    canvas->generateNewLandscape(5);
    shared_ptr<TriPolArray> tpa_exp = canvas->getTriPolArray();

    //ACT
    shared_ptr<TriPolArray> tpa = sut->getTriPolArray();

    //ASSERT
    QVERIFY2(tpa == tpa_exp, "getTriPolArrayTest error");
}

void UserControllerTest::getZBufferAlgTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvas> canvas = sut->getLandscapeCanvas();
    shared_ptr<ZBufferAlg> zba_exp = canvas->getZBufferAlg();

    //ACT
    shared_ptr<ZBufferAlg> zba = sut->getZBufferAlg();

    //ASSERT
    QVERIFY2(zba == zba_exp, "getZBufferAlgTest error");
}

void UserControllerTest::getMultTest()
{
    //ARRANGE
    int mult_exp = 5;
    sut->setMult(mult_exp);

    //ACT
    int mult = sut->getMult();

    //ASSERT
    QVERIFY2(mult == mult_exp, "getMultTest error");
}

void UserControllerTest::getImgWidthTest()
{
    //ARRANGE
    int exp = 500;
    sut->setWidth(exp);

    //ACT
    int res = sut->getImgWidth();

    //ASSERT
    QVERIFY2(res == exp, "getImgWidthTest error");
}

void UserControllerTest::getImgHeightTest()
{
    //ARRANGE
    int exp = 400;
    sut->setHeight(exp);

    //ACT
    int res = sut->getImgHeight();

    //ASSERT
    QVERIFY2(res == exp, "getImgHeightTest error");
}

void UserControllerTest::cleanup()
{
    sut.reset();
}

QTEST_APPLESS_MAIN(UserControllerTest)

#include "tst_usercontrollertest.moc"
