#include <QtTest>
#include <QSqlQuery>
#include <QSqlError>

#define FILENAME "CanvasRepositoryTest.cfg"

#include "Settings.h"
#include "Repositorys/CanvasRepository.h"

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
    db = make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QPSQL"));

    QString m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString();
    int m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    QString m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString();
    QString m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString();
    QString m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString();

    /*qDebug() << Settings::get(Settings::DBHost, Settings::DataBase).toString();
    qDebug() << Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    qDebug() << Settings::get(Settings::DBName, Settings::DataBase).toString();
    qDebug() << Settings::get(Settings::DBUser, Settings::DataBase).toString();
    qDebug() << Settings::get(Settings::DBPass, Settings::DataBase).toString();
    qDebug() << Settings::get(Settings::Schema, Settings::DataBase).toString();*/

    db->setHostName(m_dbhost);
    db->setPort(m_dbport);
    db->setDatabaseName(m_dbname);
    db->setUserName(m_dbuser);
    db->setPassword(m_dbpass);

    if (!db->open())
        qDebug() << db->lastError().text();
        //QFAIL(db->lastError().text().toStdString().c_str());

    sut = CanvasRepository();
}

CanvasRepositoryTest::~CanvasRepositoryTest()
{
}

void CanvasRepositoryTest::initTestCase()
{
    /*QFile cfgDefaults(FILENAME);
    cfgDefaults.open(QIODevice::ReadOnly);
    Settings::setDefaults(cfgDefaults.readAll());

    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();
    db = make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QPSQL"));

    QString m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString();
    int m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    QString m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString();
    QString m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString();
    QString m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString();


    db->setHostName(m_dbhost);
    db->setPort(m_dbport);
    db->setDatabaseName(m_dbname);
    db->setUserName(m_dbuser);
    db->setPassword(m_dbpass);

    if (!db->open())
        QFAIL("Disconnected!");

    sut = CanvasRepository();*/

    string query = "create schema "+ m_schema + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

void CanvasRepositoryTest::init()
{
    string query = "create table if not exists "+ m_schema + ".Canvas\
            (\
                id serial primary key,\
                user_id int,\
                name text,\
                HeightsMap text,\
                TriPolArray text,\
                Color text\
            );";

    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());

    int size = 33;
    HeightsMap hm = HeightsMap(size);
    hm.diamondSquare();
    CanvasBL canvas = CanvasBL(1, 1, "CanvasName1", hm, *hm.createPoints(), 20, 150, 20);
    string u_id = std::to_string(canvas.getUserId());
    string name = canvas.getName();
    string tmp;
    canvas.getHeightsMap().toStr(tmp);
    string hm_str = tmp;
    canvas.getHeightsMapPoints().toStr(tmp);
    string hmp = tmp;
    int r, g, b;
    canvas.getColor(r, g, b);
    string c = to_string(r) + " " + to_string(g) + " " + to_string(b);

    query = "insert into " + m_schema + ".Canvas(user_id, name, HeightsMap, TriPolArray, Color) values(";
    query += u_id + ", '";
    query += name + "', '";
    query += hm_str + "', '";
    query += hmp + "', '";
    query += c + "');";

    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());


    hm.diamondSquare();
    canvas = CanvasBL(1, 1, "CanvasName2", hm, *hm.createPoints(), 10, 140, 10);
    u_id = std::to_string(canvas.getUserId());
    name = canvas.getName();
    canvas.getHeightsMap().toStr(tmp);
    hm_str = tmp;
    canvas.getHeightsMapPoints().toStr(tmp);
    hmp = tmp;
    canvas.getColor(r, g, b);
    c = to_string(r) + " " + to_string(g) + " " + to_string(b);

    query = "insert into " + m_schema + ".Canvas(user_id, name, HeightsMap, TriPolArray, Color) values(";
    query += u_id + ", '";
    query += name + "', '";
    query += hm_str + "', '";
    query += hmp + "', '";
    query += c + "');";

    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

void CanvasRepositoryTest::getCanvasByIdTest()
{
    //ARRANGE
    string query = "SELECT * FROM " + m_schema + ".Canvas;";
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
    }
    shared_ptr<CanvasBL> canvas;

    //ACT
    try
    {
        canvas = sut.getCanvas(last_canvas_id);
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

    QVERIFY2(*canvas == *same_canvas, "getCanvasByIdTest error");
}

void CanvasRepositoryTest::getCanvasByNameTest()
{
    //ARRANGE
    string query = "SELECT * FROM " + m_schema + ".Canvas;";
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
    }
    shared_ptr<CanvasBL> canvas;

    //ACT
    try
    {
        canvas = sut.getCanvas(last_canvas_name);
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

    QVERIFY2(*canvas == *same_canvas, "getCanvasByNameTest error");
}

void CanvasRepositoryTest::getCanvasesByUidTest()
{

    //ARRANGE
    int u_id = 1;
    string query = "SELECT id, name FROM " + m_schema + ".Canvas where user_id = " + std::to_string(u_id) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    vector<pair<int, string> > same_canvases;
    while (q.next())
    {
        int id = q.value(0).toInt();
        string name = q.value(1).toString().toStdString();

        same_canvases.push_back(make_pair(id, name));
    }
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

    for (int i = 0; i < same_canvases.size(); i++)
    {
        QString msg = QString("i = %1 canvases.id = %2; canvases.name = %3; same_canvases.id = %4; same_canvases.name = %5;").
                arg(QString::number(i),QString::number(canvases[i].first), QString::fromStdString(canvases[i].second),
                    QString::number(same_canvases[i].first), QString::fromStdString(same_canvases[i].second));
        QVERIFY2(canvases[i] == same_canvases[i], msg.toStdString().c_str());
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

    string query = "SELECT * FROM " + m_schema + ".Canvas where id=" + to_string(id) + ";";
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
    }

    QVERIFY2(canvas == *same_canvas, "addCanvasTest error");
}

void CanvasRepositoryTest::deleteCanvasTest()
{
    //ARRANGE в init()

    //ACT
    try
    {
        sut.deleteCanvas(1);
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

    string query = "SELECT * FROM " + m_schema + ".Canvas where id=" + to_string(1) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
        QFAIL("Canvas is not deleted");
}

void CanvasRepositoryTest::updateCanvasTest()
{
    //ARRANGE
    int size = 33;
    HeightsMap hm = HeightsMap(size);
    hm.diamondSquare();
    CanvasBL canvas = CanvasBL(1, 1, "CanvasName", hm, *hm.createPoints(), 20, 150, 20);
    shared_ptr<CanvasBL> same_canvas;

    //ACT
    try
    {
        sut.updateCanvas(canvas, 1);
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

    string query = "SELECT * FROM " + m_schema + ".Canvas where id=" + to_string(1) + ";";
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
    }

    QVERIFY2(canvas.getHeightsMap() == same_canvas->getHeightsMap(), "HeightsMap difference");
    QVERIFY2(canvas.getHeightsMapPoints() == same_canvas->getHeightsMapPoints(), "TriPolMas difference");
    int r1, g1, b1, r2, g2, b2;
    canvas.getColor(r1, g1, b1);
    same_canvas->getColor(r2, g2, b2);
    QVERIFY2(r1 == r2, "red difference");
    QVERIFY2(g1 == g2, "green difference");
    QVERIFY2(b1 == b2, "blue difference");
}

void CanvasRepositoryTest::cleanup()
{
    string query = "drop table " + m_schema + ".Canvas cascade;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

void CanvasRepositoryTest::cleanupTestCase()
{
    string query = "drop schema " + m_schema + " cascade;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

QTEST_GUILESS_MAIN(CanvasRepositoryTest)

#include "tst_canvasrepositorytest.moc"
