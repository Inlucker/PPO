#include <QtTest>

// add necessary includes here
#include "LandscapeCanvasMock.h"
#include "Controllers/ModeratorCanvasesController.h"

template <typename A, typename B>
bool isTypeAndValEq(A var1, B var2)
{
    return false;
}

template <typename A>
bool isTypeAndValEq(A var1, A var2)
{
    return var1==var2;
}

MATCHER_P(areTypeAndValEq, val, "") { return isTypeAndValEq(arg, val); }

MATCHER_P(IsDivisibleBy, n, "") { *result_listener << "where the remainder is " << (arg % n); return (arg % n) == 0; }

using namespace testing;

class QtTestPrinter : public ::testing::EmptyTestEventListener
{
    // Called after a failed assertion or a SUCCESS().
    virtual void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override
    {
        if (test_part_result.failed())
        {
            if (test_part_result.file_name())
            {
                string msg = "Failure in";
                msg += test_part_result.file_name();
                msg += ":";
                msg += std::to_string(test_part_result.line_number());
                msg += "\n";
                msg += test_part_result.summary();
                QFAIL(msg.c_str());
            }
            else
                QFAIL(test_part_result.summary());
        }
    }
};

class ModeratorCanvasesControllerTest : public QObject
{
    Q_OBJECT

public:
    ModeratorCanvasesControllerTest();
    ~ModeratorCanvasesControllerTest();

private slots:
    void init();

    void noParamsConstructorTest();
    void selectCanvasTest();
    void getFrameBufferTest();
    void cleanCanvasTest();
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
    unique_ptr<ModeratorCanvasesController> sut;
};

ModeratorCanvasesControllerTest::ModeratorCanvasesControllerTest()
{
    /*Point p, p1(1,2,3);
    const Point& p2 = p;
    int t = 2;
    cout << typeid(p).name() << endl;
    cout << typeid(p2).name() << endl;
    cout << isTypeEq(p, p1) << endl;
    cout << isTypeEq(p, p2) << endl;
    cout << isTypeEq(p, t) << endl;*/
}

ModeratorCanvasesControllerTest::~ModeratorCanvasesControllerTest()
{

}

void ModeratorCanvasesControllerTest::init()
{
    sut = make_unique<ModeratorCanvasesController>();
}

void ModeratorCanvasesControllerTest::noParamsConstructorTest()
{
    //ARRANGE no need
    shared_ptr<LandscapeCanvas> same_canvas = make_shared<LandscapeCanvas>();

    //ACT
    sut = make_unique<ModeratorCanvasesController>();

    //ASSERT
    shared_ptr<LandscapeCanvas> canvas = dynamic_pointer_cast<LandscapeCanvas>(sut->getLandscapeCanvas());
    if (!canvas)
        QFAIL("dynamic_pointer_cast error");
    QVERIFY2(*same_canvas == *canvas, "selectCanvasTest error");
}

void ModeratorCanvasesControllerTest::selectCanvasTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();

    //ACT
    sut->selectCanvas(canvas_mock_ptr);

    //ASSERT
    shared_ptr<LandscapeCanvasI> canvas_ptr = sut->getLandscapeCanvas();
    QVERIFY2(canvas_mock_ptr == canvas_ptr, "selectCanvasTest error");
}

void ModeratorCanvasesControllerTest::getFrameBufferTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    EXPECT_CALL(*canvas_mock_ptr, generateNewLandscape(5)).Times(1);
    canvas_mock_ptr->generateNewLandscape(5);
    EXPECT_CALL(*canvas_mock_ptr, getZBufferAlg()).Times(1);
    EXPECT_CALL(*canvas_mock_ptr, getTriPolArray()).Times(1);
    canvas_mock_ptr->getZBufferAlg()->execute(*canvas_mock_ptr->getTriPolArray());
    EXPECT_CALL(*canvas_mock_ptr, getFrameBuffer()).Times(2);
    shared_ptr<FrameBuffer> same_frame_buffer = canvas_mock_ptr->getFrameBuffer();
    sut->selectCanvas(canvas_mock_ptr);
    //EXPECT_CALL(*canvas_mock_ptr, getFrameBuffer()).Times(1);

    //ACT
    shared_ptr<FrameBuffer> frame_buffer = sut->getFrameBuffer();

    //ASSERT
    QVERIFY2(frame_buffer == same_frame_buffer, "getFrameBufferTest error");
    QVERIFY2(*frame_buffer == *same_frame_buffer, "getFrameBufferTest error");
}

void ModeratorCanvasesControllerTest::cleanCanvasTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    sut->selectCanvas(canvas_mock_ptr);
    EXPECT_CALL(*canvas_mock_ptr, cleanCanvas()).Times(1);

    //ACT
    sut->cleanCanvas();

    //ASSERT in QtTestPrinter
}

using ::testing::Matcher;
void ModeratorCanvasesControllerTest::transformTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    Point p1(1, 1, 1), p2(2, 2, 2), p3(3, 3, 3);
    sut->selectCanvas(canvas_mock_ptr);
    //EXPECT_CALL(*canvas_mock_ptr, transform(TypedEq<const Point&>(p1), TypedEq<const Point&>(p1), TypedEq<const Point&>(p1))).Times(1);
    EXPECT_CALL(*canvas_mock_ptr, transform(areTypeAndValEq(p1), areTypeAndValEq(p2), areTypeAndValEq(p3))).Times(1);

    //ACT
    sut->transform(p1, p2, p3);

    //ASSERT in QtTestPrinter
}

void ModeratorCanvasesControllerTest::moveTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    Point p(1, 2, 3);
    sut->selectCanvas(canvas_mock_ptr);
    EXPECT_CALL(*canvas_mock_ptr, move(areTypeAndValEq(p))).Times(1);

    //ACT
    sut->move(p);

    //ASSERT in QtTestPrinter
}

void ModeratorCanvasesControllerTest::scaleTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    Point p(1, 2, 3);
    sut->selectCanvas(canvas_mock_ptr);
    EXPECT_CALL(*canvas_mock_ptr, scale(areTypeAndValEq(p))).Times(1);

    //ACT
    sut->scale(p);

    //ASSERT in QtTestPrinter
}

void ModeratorCanvasesControllerTest::rotateTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    Point p(1, 2, 3);
    sut->selectCanvas(canvas_mock_ptr);
    EXPECT_CALL(*canvas_mock_ptr, rotate(areTypeAndValEq(p))).Times(1);

    //ACT
    sut->rotate(p);

    //ASSERT in QtTestPrinter
}

void ModeratorCanvasesControllerTest::getColorTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    sut->selectCanvas(canvas_mock_ptr);
    int r = 1, g = 2, b = 3;
    EXPECT_CALL(*canvas_mock_ptr, getColor(TypedEq<int&>(r), TypedEq<int&>(g), TypedEq<int&>(b))).Times(1);

    //ACT
    sut->getColor(r, g, b);

    //ASSERT in QtTestPrinter
}

void ModeratorCanvasesControllerTest::getLandscapeCanvasTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    sut->selectCanvas(canvas_mock_ptr);

    //ACT
    shared_ptr<LandscapeCanvasI> canvas_ptr = sut->getLandscapeCanvas();

    //ASSERT
    QVERIFY2(canvas_mock_ptr == canvas_ptr, "getLandscapeCanvasTest error");
}

void ModeratorCanvasesControllerTest::getHeightsMapTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    EXPECT_CALL(*canvas_mock_ptr, generateNewLandscape(5)).Times(1);
    canvas_mock_ptr->generateNewLandscape(5);
    EXPECT_CALL(*canvas_mock_ptr, getHeightsMap()).Times(2);
    shared_ptr<HeightsMap> same_heigths_map = canvas_mock_ptr->getHeightsMap();
    sut->selectCanvas(canvas_mock_ptr);
    //EXPECT_CALL(*canvas_mock_ptr, getHeightsMap()).Times(1);

    //ACT
    //EXPECT_EQ(same_heigths_map, canvas_mock_ptr->getHeightsMap());
    shared_ptr<HeightsMap> heights_map = sut->getHeightsMap();

    //ASSERT
    QVERIFY2(heights_map == same_heigths_map, "getHeightsMapTest error");
    QVERIFY2(*heights_map == *same_heigths_map, "getHeightsMapTest error");
}

void ModeratorCanvasesControllerTest::getHeightsMapPointsTest()
{
    /* classic style
    //ARRANGE
    shared_ptr<LandscapeCanvas> canvas = make_shared<LandscapeCanvas>();
    canvas->generateNewLandscape(33);
    shared_ptr<HeightsMapPoints> same_heigths_map_points = canvas->getHeightsMapPoints();
    sut->selectCanvas(canvas);

    //ACT
    shared_ptr<HeightsMapPoints> heigths_map_point = sut->getHeightsMapPoints();

    //ASSERT
    QVERIFY2(heigths_map_point == same_heigths_map_points, "getHeightsMapTest error");
    QVERIFY2(*heigths_map_point == *same_heigths_map_points, "getHeightsMapTest error");*/

    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    EXPECT_CALL(*canvas_mock_ptr, generateNewLandscape(5)).Times(1);
    canvas_mock_ptr->generateNewLandscape(5);
    EXPECT_CALL(*canvas_mock_ptr, getHeightsMapPoints()).Times(2);
    shared_ptr<HeightsMapPoints> same_heigths_map_points = canvas_mock_ptr->getHeightsMapPoints();
    sut->selectCanvas(canvas_mock_ptr);
    //EXPECT_CALL(*canvas_mock_ptr, getHeightsMapPoints()).Times(1);

    //ACT
    shared_ptr<HeightsMapPoints> heigths_map_point = sut->getHeightsMapPoints();

    //ASSERT
    QVERIFY2(heigths_map_point == same_heigths_map_points, "getHeightsMapPointsTest error");
    QVERIFY2(*heigths_map_point == *same_heigths_map_points, "getHeightsMapPointsTest error");
}

void ModeratorCanvasesControllerTest::getTriPolArrayTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    EXPECT_CALL(*canvas_mock_ptr, generateNewLandscape(5)).Times(1);
    canvas_mock_ptr->generateNewLandscape(5);
    EXPECT_CALL(*canvas_mock_ptr, getTriPolArray()).Times(2);
    shared_ptr<TriPolArray> same_tpa = canvas_mock_ptr->getTriPolArray();
    sut->selectCanvas(canvas_mock_ptr);
    //EXPECT_CALL(*canvas_mock_ptr, getTriPolArray()).Times(1);

    //ACT
    shared_ptr<TriPolArray> tpa = sut->getTriPolArray();

    //ASSERT
    QVERIFY2(tpa == same_tpa, "getTriPolArrayTest error");
    QVERIFY2(*tpa == *same_tpa, "getTriPolArrayTest error");
}

void ModeratorCanvasesControllerTest::getZBufferAlgTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    EXPECT_CALL(*canvas_mock_ptr, getZBufferAlg()).Times(2);
    shared_ptr<ZBufferAlg> same_zbuffer_alg = canvas_mock_ptr->getZBufferAlg();
    sut->selectCanvas(canvas_mock_ptr);
    //EXPECT_CALL(*canvas_mock_ptr, getZBufferAlg()).Times(1);

    //ACT
    shared_ptr<ZBufferAlg> zbuffer_alg = sut->getZBufferAlg();

    //ASSERT
    QVERIFY2(zbuffer_alg == same_zbuffer_alg, "getZBufferAlgTest error");
}

void ModeratorCanvasesControllerTest::getMultTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    EXPECT_CALL(*canvas_mock_ptr, getMult()).Times(2);
    int same_mult = canvas_mock_ptr->getMult();
    sut->selectCanvas(canvas_mock_ptr);

    //ACT
    int mult = sut->getMult();

    //ASSERT
    QVERIFY2(mult == same_mult, "getMultTest error");
}

void ModeratorCanvasesControllerTest::getImgWidthTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    EXPECT_CALL(*canvas_mock_ptr, getImgWidth()).Times(2);
    int same_width = canvas_mock_ptr->getImgWidth();
    sut->selectCanvas(canvas_mock_ptr);

    //ACT
    int width = sut->getImgWidth();

    //ASSERT
    QVERIFY2(width == same_width, "getImgWidthTest error");
}

void ModeratorCanvasesControllerTest::getImgHeightTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    EXPECT_CALL(*canvas_mock_ptr, getImgHeight()).Times(2);
    int same_height = canvas_mock_ptr->getImgHeight();
    sut->selectCanvas(canvas_mock_ptr);

    //ACT
    int height = sut->getImgHeight();

    //ASSERT
    QVERIFY2(height == same_height, "getImgHeightTest error");
}

void ModeratorCanvasesControllerTest::cleanup()
{
    sut.reset();
}

//QTEST_APPLESS_MAIN(ModeratorCanvasesControllerTest)

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners =
            ::testing::UnitTest::GetInstance()->listeners();
    delete listeners.Release(listeners.default_result_printer());
    listeners.Append(new QtTestPrinter);

    TESTLIB_SELFCOVERAGE_START(ModeratorCanvasesControllerTest)
    ModeratorCanvasesControllerTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}

#include "tst_moderatorcanvasescontrollertest.moc"
