#include <QtTest>
#include <QSqlQuery>
#include <QSqlError>

#define FILENAME "ParamsRepositoryTest.cfg"

#include "Settings.h"
#include "Repositorys/ParamsRepository.h"
#include "Errors/RepositoryErrors.h"

class ParamsRepositoryTest : public QObject
{
    Q_OBJECT

public:
    ParamsRepositoryTest();
    ~ParamsRepositoryTest();

private slots:
    void initTestCase();
    void init();

    void getParamsTest();
    //void addParamsTest();
    //void deleteParamsTest();
    //void updateParamsTest();

    void cleanup();
    void cleanupTestCase();

    private:
    string m_schema;
    unique_ptr<QSqlDatabase> db;
    ParamsRepository sut;
};

ParamsRepositoryTest::ParamsRepositoryTest()
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


    db->setHostName(m_dbhost);
    db->setPort(m_dbport);
    db->setDatabaseName(m_dbname);
    db->setUserName(m_dbuser);
    db->setPassword(m_dbpass);

    if (!db->open())
        QFAIL("Disconnected!");

    sut = ParamsRepository();
}

ParamsRepositoryTest::~ParamsRepositoryTest()
{

}

void ParamsRepositoryTest::initTestCase()
{
    string query = "create schema " + m_schema + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

void ParamsRepositoryTest::init()
{
    string query = "create table if not exists " + m_schema + ".Params\
                    (\
                        canvas_id int unique,\
                        FOREIGN KEY (canvas_id) REFERENCES PPO.Canvas (id),\
                        width int,\
                        height int,\
                        range float,\
                        smooth bool,\
                        mult int,\
                        red int,\
                        green int,\
                        blue int,\
                        size int\
                    );";

    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());

    query = "insert into " + m_schema + ".Params values (1, 960, 540, 24.75, true, 1, 120, 31, 150, 33);\
            insert into " + m_schema + ".Params values (2, 768, 432, 24.75, false, 4, 120, 31, 150, 33);\
            insert into " + m_schema + ".Params values (3, 960, 540, 24.75, true, 1, 120, 31, 150, 33);\
            insert into " + m_schema + ".Params values (4, 960, 540, 24.75, true, 1, 120, 31, 150, 33);";

    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

void ParamsRepositoryTest::getParamsTest()
{
    //ARRANGE in init()
    shared_ptr<ParamsBL> params, same_params;
    string login = "user1";
    string password = "123";

    //ACT
    try
    {
        params = sut.getParams(1);
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

    string query = "SELECT * FROM " + m_schema + ".Params where canvas_id=" + to_string(1) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
    {
        int c_id = q.value(0).toInt();
        int width = q.value(1).toInt();
        int height = q.value(2).toInt();
        double range = q.value(3).toDouble();
        bool smooth = q.value(4).toBool();
        int mult = q.value(5).toInt();
        int red = q.value(6).toInt();
        int green = q.value(7).toInt();
        int blue = q.value(8).toInt();
        int size = q.value(9).toInt();

        same_params =  make_shared<ParamsBL>(c_id, width, height, range, smooth, mult, red, green, blue, size);
    }

    QVERIFY2(*params == *same_params, "getParamsTest error");
}

void ParamsRepositoryTest::cleanup()
{
    string query = "drop table " + m_schema + ".Params cascade;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

void ParamsRepositoryTest::cleanupTestCase()
{
    string query = "drop schema " + m_schema + " cascade;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

QTEST_APPLESS_MAIN(ParamsRepositoryTest)

#include "tst_paramsrepositorytest.moc"
