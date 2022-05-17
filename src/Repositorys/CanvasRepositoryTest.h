#ifndef CANVASREPOSITORYTEST_H
#define CANVASREPOSITORYTEST_H

#include "CanvasRepository.h"

class CanvasRepositoryTest : public CanvasRepository
{
public:
    CanvasRepositoryTest();
    //CanvasRepositoryTest(string dbhost, int dbport, string dbname, string dbuser, string dbpass, string dbschema);
    virtual ~CanvasRepositoryTest();

    int testAll();

    const string& getOutput() const;

private:
    void setupForTest();

    int addGetCanvasTest();
    int updateCanvasTest();
    int deleteCanvasTest();

private:
    //shared_ptr<CanvasRepository> canvas_rep;
    //string schema = "CanvasRepositoryTest";
    int errors_count = 0;
    string output = "";
};

#endif // CANVASREPOSITORYTEST_H
