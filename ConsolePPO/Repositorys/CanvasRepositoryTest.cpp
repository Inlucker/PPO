#include "CanvasRepositoryTest.h"

CanvasRepositoryTest::CanvasRepositoryTest()
    : CanvasRepository("postgres", "postgres", "CanvasRepositoryTest", "localhost", 5432, "postgres")
{
    setupForTest();
    errors_count = testAll();
    output += "Errors count: " + to_string(errors_count) + "\n";
}

CanvasRepositoryTest::~CanvasRepositoryTest()
{
    cout << "CanvasRepositoryTest destructor";
    connect();
    string query = "drop schema " + m_dbschema + " cascade;";
    PQsendQuery(m_connection.get(), query.c_str());

    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout << PQresultErrorMessage(res);
        }
        PQclear(res);
    }
}

int CanvasRepositoryTest::testAll()
{
    int res = 0;

    res += addGetCanvasTest() + updateCanvasTest() + deleteCanvasTest();

    return res;
}

/*CanvasRepositoryTest::CanvasRepositoryTest(string dbhost, int dbport, string dbname, string dbuser, string dbpass, string dbschema) :
    CanvasRepository(dbhost, dbport, dbname, dbuser, dbpass, dbschema)
{
    setupForTest();
}*/

int CanvasRepositoryTest::addGetCanvasTest()
{
    int res = 0;

    int size = 33;
    HeightsMap hm = HeightsMap(size);
    hm.diamondSquare();
    //shared_ptr<HeightsMapPoints> hmp = hm.createPoints();
    CanvasBL canvas = CanvasBL(1, "CanvasName", hm, *hm.createPoints(), 20, 150, 20);

    shared_ptr<CanvasBL> same_canvas;
    try
    {
        this->addCanvas(canvas);
        same_canvas = this->getCanvas(1);
    }
    catch (BaseError &er)
    {
        res++;
        output += "addGetCanvasTest error\n";
        return res;
    }
    catch (...)
    {
        res++;
        output += "addGetCanvasTest error\n";
        return res;
    }

    if (canvas != *same_canvas)
    {
        res++;
        output += "addGetCanvasTest error\n";
    }
    else
    {
        output += "addGetCanvasTest OK\n";
    }

    return res;
}

int CanvasRepositoryTest::updateCanvasTest()
{
    int res = 0;

    int size = 33;
    HeightsMap hm = HeightsMap(size);
    hm.diamondSquare();
    CanvasBL canvas = CanvasBL(1, "CanvasName", hm, *hm.createPoints(), 20, 150, 20);

    shared_ptr<CanvasBL> same_canvas;
    try
    {
        this->updateCanvas(canvas, 1);
        same_canvas = this->getCanvas(1);
    }
    catch (BaseError &er)
    {
        res++;
        output += "updateCanvasTest error\n";
        return res;
    }
    catch (...)
    {
        res++;
        output += "updateCanvasTest error\n";
        return res;
    }

    if (canvas != *same_canvas)
    {
        res++;
        output += "updateCanvasTest error\n";
    }
    else
        output += "updateCanvasTest OK\n";

    return res;
}

int CanvasRepositoryTest::deleteCanvasTest()
{
    int res = 0;

    try
    {
        this->deleteCanvas(1);
    }
    catch (DeleteCanvasError &er)
    {
        //ok
    }
    catch (...)
    {
        output += "deleteCanvasTest error (couldn't delete)\n";
        res++;
        return res;
    }

    try
    {
        this->getCanvas(1);
        res++;
        output += "deleteCanvasTest (didn't delete) error\n";
    }
    catch (GetCanvasError &er)
    {
        //ok
        output += "deleteCanvasTest OK\n";
    }
    catch (...)
    {
        output += "deleteCanvasTest (unexpected getCanvas error) error\n";
        res++;
        return res;
    }

    return res;
}

const string &CanvasRepositoryTest::getOutput() const
{
    return output;
}

void CanvasRepositoryTest::setupForTest()
{
    connect();
    string query = "create schema "+ m_dbschema + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout << PQresultErrorMessage(res);
        }
        PQclear(res);
    }

    connect();
    query = "create table if not exists "+ m_dbschema + ".Canvas\
            (\
                id serial primary key,\
                user_id int,\
                FOREIGN KEY (user_id) REFERENCES PPO.Users (id),\
                name text,\
                HeightsMap text,\
                TriPolArray text,\
                Color text\
            );";
    PQsendQuery(m_connection.get(), query.c_str());

    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout << PQresultErrorMessage(res);
        }

        PQclear(res);
    }
}
