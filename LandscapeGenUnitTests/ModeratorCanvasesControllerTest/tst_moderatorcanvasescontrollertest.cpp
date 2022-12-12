#include <QtTest>

// add necessary includes here
#include "LandscapeCanvasMock.h"
#include "Controllers/ModeratorCanvasesController.h"

using namespace testing;

class QtTestPrinter : public ::testing::EmptyTestEventListener
{
    // Called after a failed assertion or a SUCCESS().
    virtual void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override
    {
        if (test_part_result.failed())
        {
            string msg = "Failure in";
            msg += test_part_result.file_name();
            msg += ":";
            msg += std::to_string(test_part_result.line_number());
            msg += "\n";
            msg += test_part_result.summary();
            QFAIL(msg.c_str());
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
    //void noParamsConstructorTest();
    //void selectCanvasTest();
    //void getFrameBufferTest();
    void cleanCanvasTest();
    //void transformTest();
    //void moveTest();
    //void scaleTest();
    //void rotateTest();
    //void getColorTest();
    //void getLandscapeCanvasTest();
    //void getHeightsMapTest();
    //void getHeightsMapPointsTest();
    //void getTriPolArrayTest();
    //void getZBufferAlgTest();
    //void getMultTest();
    //void getImgWidthTest();
    //void getImgHeightTest();

    void cleanup();

private:
    unique_ptr<ModeratorCanvasesController> sut;
};

ModeratorCanvasesControllerTest::ModeratorCanvasesControllerTest()
{

}

ModeratorCanvasesControllerTest::~ModeratorCanvasesControllerTest()
{

}

void ModeratorCanvasesControllerTest::cleanCanvasTest()
{
    //ARRANGE
    shared_ptr<LandscapeCanvasMock> canvas_mock_ptr = make_shared<LandscapeCanvasMock>();
    sut = make_unique<ModeratorCanvasesController>();
    sut->selectCanvas(canvas_mock_ptr);

    //ACT
    EXPECT_CALL(*canvas_mock_ptr, cleanCanvas()).Times(1);
    sut->cleanCanvas();

    //ASSERT in QtTestPrinter
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
