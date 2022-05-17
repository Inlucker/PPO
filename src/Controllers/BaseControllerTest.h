#ifndef BASECONTROLLERTEST_H
#define BASECONTROLLERTEST_H

#include "BaseController.h"

class BaseControllerTest
{
public:
    BaseControllerTest();

    int noParamsConstrcutorTest();
    int userBLConstrcutorTest();
    int loginTest();
    int logoutTest();
    int getUserTest();

    const string& getOutput() const;

private:
    int errors_count = 0;
    string output;
};

#endif // BASECONTROLLERTEST_H
