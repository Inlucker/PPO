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
    string m_dbhost;
    int m_dbport;
    string m_dbname;
    string m_dbuser;
    string m_dbpass;
    string m_dbschema;

    int errors_count = 0;
    string output = "";
};

#endif // CANVASREPOSITORYTEST_H
