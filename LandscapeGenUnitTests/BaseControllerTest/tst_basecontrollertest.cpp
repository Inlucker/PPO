#include <QtTest>

// add necessary includes here
#include "Controllers/BaseController.h"

class BaseControllerTest : public QObject
{
    Q_OBJECT

public:
    BaseControllerTest();
    ~BaseControllerTest();

private slots:
    void noParamsConstrcutorTest();
    void userBLConstrcutorTest();
    void loginTest();
    void logoutTest();
    void getUserTest();

    void cleanup();

private:
    BaseController* sut;
};

BaseControllerTest::BaseControllerTest()
{

}

BaseControllerTest::~BaseControllerTest()
{

}

void BaseControllerTest::noParamsConstrcutorTest()
{
    //ARRANGE no need

    //ACT
    sut = new BaseController();

    //ASSERT
    shared_ptr<UserBL> ubl = sut->getUser();
    UserBL same_ubl = UserBL();
    QVERIFY2(*ubl == same_ubl, "Error in noParamsConstrcutorTest");
}

void BaseControllerTest::userBLConstrcutorTest()
{
    //ARRANGE
    shared_ptr<UserBL> same_ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);

    //ACT
    sut = new BaseController(same_ubl);

    shared_ptr<UserBL> ubl = sut->getUser();

    //ASSERT
    QVERIFY2(*ubl == *same_ubl, "Error in userBLConstrcutorTest");
}

void BaseControllerTest::loginTest()
{
    //ARRANGE
    sut  = new BaseController();
    shared_ptr<UserBL> same_ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);

    //ACT
    sut->login(same_ubl);

    //ASSERT
    shared_ptr<UserBL> ubl = sut->getUser();
    QVERIFY2(*ubl == *same_ubl, "Error in loginTest");
}

void BaseControllerTest::logoutTest()
{
    //ARRANGE
    shared_ptr<UserBL> same_ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    sut  = new BaseController(same_ubl);

    //ACT
    sut->logout();

    //ASSERT
    shared_ptr<UserBL> ubl = sut->getUser();
    QVERIFY2(ubl == nullptr, "Error in logoutTest");
}

void BaseControllerTest::getUserTest()
{
    //ARRANGE
    shared_ptr<UserBL> same_ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    sut = new BaseController(same_ubl);

    //ACT
    shared_ptr<UserBL> ubl = sut->getUser();

    //ASSERT
    QVERIFY2(*ubl == *same_ubl, "Error in getUserTest");
}

void BaseControllerTest::cleanup()
{
    delete sut;
    sut = NULL;
}

QTEST_APPLESS_MAIN(BaseControllerTest)

#include "tst_basecontrollertest.moc"
