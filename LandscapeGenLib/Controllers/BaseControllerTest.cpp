#include "BaseControllerTest.h"

#include <iostream>
using namespace std;

BaseControllerTest::BaseControllerTest()
{
    /*cout << noParamsConstrcutorTest() << endl;
    cout << userBLConstrcutorTest() << endl;
    cout << loginTest() << endl;
    cout << logoutTest() << endl;
    cout << getUserTest() << endl;*/

    output = "";
    errors_count =  noParamsConstrcutorTest() +
                    userBLConstrcutorTest() +
                    loginTest() +
                    logoutTest() +
                    getUserTest();

    output += "Errors count: " + to_string(errors_count) + "\n";
    //cout << output;
}

int BaseControllerTest::noParamsConstrcutorTest()
{
    int res = 0;
    BaseController bc = BaseController();
    shared_ptr<UserBL> ubl = bc.getUser();
    UserBL an_ubl = UserBL();
    if (*ubl != an_ubl)
    {
        output += "Error in noParamsConstrcutorTest";
        res++;
    }
    else
        output += "noParamsConstrcutorTest OK\n";
    return res;
}

int BaseControllerTest::userBLConstrcutorTest()
{
    int res = 0;
    shared_ptr<UserBL> ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    BaseController bc = BaseController(ubl);
    shared_ptr<UserBL> bc_ubl = bc.getUser();
    if (*bc_ubl != *ubl)
    {
        output += "Error in userBLConstrcutorTest";
        res++;
    }
    else
        output += "userBLConstrcutorTest OK\n";
    return res;
}

int BaseControllerTest::loginTest()
{
    int res = 0;
    BaseController bc = BaseController();
    shared_ptr<UserBL> ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    bc.login(ubl);
    shared_ptr<UserBL> bc_ubl = bc.getUser();
    if (*bc_ubl != *ubl)
    {
        output += "Error in loginTest";
        res++;
    }
    else
        output += "loginTest OK\n";
    return res;
}

int BaseControllerTest::logoutTest()
{
    int res = 0;
    BaseController bc = BaseController();
    shared_ptr<UserBL> ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    bc.login(ubl);
    bc.logout();
    shared_ptr<UserBL> bc_ubl = bc.getUser();
    if (bc_ubl != nullptr)
    {
        output += "Error in logoutTest";
        res++;
    }
    else
        output += "logoutTest OK\n";
    return res;
}

int BaseControllerTest::getUserTest()
{
    int res = 0;
    shared_ptr<UserBL> ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    BaseController bc = BaseController(ubl);
    shared_ptr<UserBL> bc_ubl = bc.getUser();
    if (*bc_ubl != *ubl)
    {
        output += "Error in getUserTest";
        res++;
    }
    else
        output += "getUserTest OK\n";
    return res;
}

const string &BaseControllerTest::getOutput() const
{
    return output;
}
