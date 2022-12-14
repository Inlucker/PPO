#include <QtTest>
#include <QSqlQuery>
#include <QSqlError>

#define FILENAME "CanvasRepositoryTest.cfg"

#include "Settings.h"
#include "Repositorys/CanvasRepository.h"
#include "common.h"

class CanvasRepositoryTest : public QObject
{
    Q_OBJECT

public:
    CanvasRepositoryTest();
    ~CanvasRepositoryTest();

private slots:
    void initTestCase();
    void init();

    void getCanvasByIdTest();
    void getCanvasByNameTest();
    void getCanvasesByUidTest();
    void addCanvasTest();
    void deleteCanvasTest();
    void updateCanvasTest();

    void cleanup();
    void cleanupTestCase();

private:
    string m_schema;
    unique_ptr<QSqlDatabase> db;
    CanvasRepository sut;
};

CanvasRepositoryTest::CanvasRepositoryTest()
{
    QFile cfgDefaults(FILENAME);
    cfgDefaults.open(QIODevice::ReadOnly);
    Settings::setDefaults(cfgDefaults.readAll());

    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();

    QString m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString();
    int m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    QString m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString();
    QString m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString();
    QString m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString();

    /*db = make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QPSQL"));
    db->setHostName(m_dbhost);
    db->setPort(m_dbport);
    db->setDatabaseName(m_dbname);
    db->setUserName(m_dbuser);
    db->setPassword(m_dbpass);

    if (!db->open())
        qDebug() << db->lastError().text();
        //QFAIL(db->lastError().text().toStdString().c_str());*/

    db = DataBaseBuilder::createPostgresDataBase(m_dbhost, m_dbport, m_dbname, m_dbuser, m_dbpass, m_schema);

    sut = CanvasRepository();
}

CanvasRepositoryTest::~CanvasRepositoryTest()
{
}

void CanvasRepositoryTest::initTestCase()
{
    if (DataBaseBuilder::createSchema() != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
    /*string query = "create schema "+ m_schema + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());*/
}

void CanvasRepositoryTest::init()
{
    if (DataBaseBuilder::createCanvasTable(m_schema) != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());

    if (DataBaseBuilder::fillCanvasTable(2) != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
    /*int size = 33;
    HeightsMap hm = HeightsMap(size);
    hm.diamondSquare();
    CanvasBL canvas = CanvasBL(1, 1, "CanvasName1", hm, *hm.createPoints(), 20, 150, 20);

    DataBaseBuilder::insertCanvasTable(canvas, m_schema);

    hm.diamondSquare();
    canvas = CanvasBL(1, 1, "CanvasName2", hm, *hm.createPoints(), 10, 140, 10);
    DataBaseBuilder::insertCanvasTable(canvas, m_schema);*/
}

void CanvasRepositoryTest::getCanvasByIdTest()
{
    //ARRANGE
    shared_ptr<CanvasBL> canvas_exp;
    if (DataBaseBuilder::getCanvas(canvas_exp, 1) != OK || !canvas_exp)
        QFAIL(DataBaseBuilder::lastError().c_str());
    int canvas_id = canvas_exp->getId();
    /*string query = "SELECT * FROM " + m_schema + ".Canvas;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    int last_canvas_id = -1;
    shared_ptr<CanvasBL> same_canvas;
    if (q.next())
    {
        last_canvas_id = q.value(0).toInt();
        int u_id = q.value(1).toInt();
        string name = q.value(2).toString().toStdString();
        string hm = q.value(3).toString().toStdString();
        string tpa = q.value(4).toString().toStdString();
        string c = q.value(5).toString().toStdString();

        same_canvas = make_shared<CanvasBL>(last_canvas_id, u_id, name, hm, tpa, c);
    }*/
    shared_ptr<CanvasBL> canvas;

    //ACT
    try
    {
        canvas = sut.getCanvas(canvas_id);
    }
    //ASSERT
    catch (BaseError &er)
    {
        QFAIL(er.what());
        return;
    }
    catch (...)
    {
        QFAIL("Unexpected error");
        return;
    }

    QVERIFY2(*canvas == *canvas_exp, "getCanvasByIdTest error");
}

void CanvasRepositoryTest::getCanvasByNameTest()
{
    //ARRANGE
    shared_ptr<CanvasBL> canvas_exp;
    if (DataBaseBuilder::getCanvas(canvas_exp, 1) != OK || !canvas_exp)
        QFAIL(DataBaseBuilder::lastError().c_str());
    string canvas_name = canvas_exp->getName();
    /*string query = "SELECT * FROM " + m_schema + ".Canvas;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    string last_canvas_name;
    shared_ptr<CanvasBL> same_canvas;
    if (q.next())
    {
        int id = q.value(0).toInt();
        int u_id = q.value(1).toInt();
        last_canvas_name = q.value(2).toString().toStdString();
        string hm = q.value(3).toString().toStdString();
        string tpa = q.value(4).toString().toStdString();
        string c = q.value(5).toString().toStdString();

        same_canvas = make_shared<CanvasBL>(id, u_id, last_canvas_name, hm, tpa, c);
    }*/
    shared_ptr<CanvasBL> canvas;

    //ACT
    try
    {
        canvas = sut.getCanvas(canvas_name);
    }
    //ASSERT
    catch (BaseError &er)
    {
        QFAIL(er.what());
        return;
    }
    catch (...)
    {
        QFAIL("Unexpected error");
        return;
    }

    QVERIFY2(*canvas == *canvas_exp, "getCanvasByNameTest error");
}

void CanvasRepositoryTest::getCanvasesByUidTest()
{
    //ARRANGE
    int u_id = 1;
    /*string query = "SELECT id, name FROM " + m_schema + ".Canvas where user_id = " + std::to_string(u_id) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    vector<pair<int, string> > same_canvases;
    while (q.next())
    {
        int id = q.value(0).toInt();
        string name = q.value(1).toString().toStdString();

        same_canvases.push_back(make_pair(id, name));
    }*/
    vector<CanvasBL> canvases_vec;
    if (DataBaseBuilder::getCanvasesByUid(canvases_vec, u_id) != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
    vector<pair<int, string> > canvases_exp;
    for (const CanvasBL& c : canvases_vec)
        canvases_exp.push_back(make_pair(c.getId(), c.getName()));
    vector<pair<int, string> > canvases;

    //ACT
    try
    {
        canvases = sut.getCanvasesByUid(u_id);
    }
    //ASSERT
    catch (BaseError &er)
    {
        QFAIL(er.what());
        return;
    }
    catch (...)
    {
        QFAIL("Unexpected error");
        return;
    }

    for (int i = 0; i < canvases_exp.size(); i++)
    {
        QString msg = QString("i = %1 canvases.id = %2; canvases.name = %3; same_canvases.id = %4; same_canvases.name = %5;").
                arg(QString::number(i),QString::number(canvases[i].first), QString::fromStdString(canvases[i].second),
                    QString::number(canvases_exp[i].first), QString::fromStdString(canvases_exp[i].second));
        QVERIFY2(canvases[i] == canvases_exp[i], msg.toStdString().c_str());
    }
}

void CanvasRepositoryTest::addCanvasTest()
{
    //ARRANGE
    int size = 33;
    HeightsMap hm = HeightsMap(size);
    hm.diamondSquare();
    CanvasBL canvas = CanvasBL(1, 1, "CanvasName", hm, *hm.createPoints(), 20, 150, 20);
    shared_ptr<CanvasBL> same_canvas;
    int id = -1;

    //ACT
    try
    {
        id = sut.addCanvas(canvas);
    }
    //ASSERT
    catch (BaseError &er)
    {
        QFAIL(er.what());
        return;
    }
    catch (...)
    {
        QFAIL("Unexpected error");
        return;
    }

    shared_ptr<CanvasBL> canvas_exp;
    if (DataBaseBuilder::getCanvas(canvas_exp, id) != OK || !canvas_exp)
        QFAIL(DataBaseBuilder::lastError().c_str());
    /*string query = "SELECT * FROM " + m_schema + ".Canvas where id=" + to_string(id) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
    {
        int id = q.value(0).toInt();
        int u_id = q.value(1).toInt();
        string name = q.value(2).toString().toStdString();
        string hm = q.value(3).toString().toStdString();
        string tpa = q.value(4).toString().toStdString();
        string c = q.value(5).toString().toStdString();

        same_canvas = make_shared<CanvasBL>(id, u_id, name, hm, tpa, c);
    }*/

    QVERIFY2(canvas == *canvas_exp, "addCanvasTest error");
}

void CanvasRepositoryTest::deleteCanvasTest()
{
    //ARRANGE в init()
    int id = 1;

    //ACT
    try
    {
        sut.deleteCanvas(id);
    }
    //ASSERT
    catch (DeleteCanvasError &er)
    {
        QFAIL(er.what());
        return;
    }
    catch (...)
    {
        QFAIL("Unexpected error");
        return;
    }

    shared_ptr<CanvasBL> canvas_exp;
    Status status = DataBaseBuilder::getCanvas(canvas_exp, id);
    if (status == EXEC_ERROR)
        QFAIL(DataBaseBuilder::lastError().c_str());
    if (status != EMPTY_RES)
        QFAIL("Canvas is not deleted");
    /*string query = "SELECT * FROM " + m_schema + ".Canvas where id=" + to_string(id) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
        QFAIL("Canvas is not deleted");*/
}

void CanvasRepositoryTest::updateCanvasTest()
{
    //ARRANGE
    int id = 1;
    int size = 33;
    HeightsMap hm = HeightsMap(size);
    hm.diamondSquare();
    CanvasBL canvas = CanvasBL(1, 1, "CanvasName", hm, *hm.createPoints(), 20, 150, 20);
    shared_ptr<CanvasBL> canvas_exp;

    //ACT
    try
    {
        sut.updateCanvas(canvas, id);
    }
    //ASSERT
    catch (BaseError &er)
    {
        QFAIL(er.what());
        return;
    }
    catch (...)
    {
        QFAIL("Unexpected error");
        return;
    }

    if (DataBaseBuilder::getCanvas(canvas_exp, id) != OK || !canvas_exp)
        QFAIL(DataBaseBuilder::lastError().c_str());
    /*string query = "SELECT * FROM " + m_schema + ".Canvas where id=" + to_string(1) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
    {
        int id = q.value(0).toInt();
        int u_id = q.value(1).toInt();
        string name = q.value(2).toString().toStdString();
        string hm = q.value(3).toString().toStdString();
        string tpa = q.value(4).toString().toStdString();
        string c = q.value(5).toString().toStdString();

        same_canvas = make_shared<CanvasBL>(id, u_id, name, hm, tpa, c);
    }*/

    QVERIFY2(canvas.getHeightsMap() == canvas_exp->getHeightsMap(), "HeightsMap difference");
    QVERIFY2(canvas.getHeightsMapPoints() == canvas_exp->getHeightsMapPoints(), "TriPolMas difference");
    int r1, g1, b1, r2, g2, b2;
    canvas.getColor(r1, g1, b1);
    canvas_exp->getColor(r2, g2, b2);
    QVERIFY2(r1 == r2, "red difference");
    QVERIFY2(g1 == g2, "green difference");
    QVERIFY2(b1 == b2, "blue difference");
}

void CanvasRepositoryTest::cleanup()
{
    if (DataBaseBuilder::dropCanvasTable() != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
    /*string query = "drop table " + m_schema + ".Canvas cascade;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());*/
}

void CanvasRepositoryTest::cleanupTestCase()
{
    if (DataBaseBuilder::dropSchemaCascade() != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
    /*string query = "drop schema " + m_schema + " cascade;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());*/
}

QTEST_GUILESS_MAIN(CanvasRepositoryTest)

#include "tst_canvasrepositorytest.moc"
