#ifndef CANVASREPOSITORYTEST_H
#define CANVASREPOSITORYTEST_H

#include "CanvasRepository.h"

class CanvasRepositoryTest : public CanvasRepository
{
public:
    CanvasRepositoryTest();
    virtual ~CanvasRepositoryTest();

    int testAll();

    const string& getOutput() const;

private:
    void setupForTest();

    int addGetCanvasTest();
    int updateCanvasTest();
    int deleteCanvasTest();

private:
    QString old_login;
    QString old_pass;
    QString old_schema;

    int errors_count = 0;
    string output = "";
};

#endif // CANVASREPOSITORYTEST_H
