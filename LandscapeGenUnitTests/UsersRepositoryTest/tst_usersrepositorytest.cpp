#include <QtTest>
#include <QSqlQuery>
#include <QSqlError>

#define FILENAME "UsersRepositoryTest.cfg"

#include "Settings.h"
#include "Repositorys/UsersRepository.h"

class UsersRepositoryTest : public QObject
{
    Q_OBJECT

public:
    UsersRepositoryTest();
    ~UsersRepositoryTest();

private slots:
    void initTestCase();
    void init();

    void getUserByLoginPassTest();
    void getCanvasUserByNameTest();
    void getFreeCanvasUsersTest();
    void getCanvasUsersByMidTest();
    void addUserTest();
    void deleteUserTest();
    void updateUserTest();

    void cleanup();
    void cleanupTestCase();

private:
    string m_schema;
    unique_ptr<QSqlDatabase> db;
    UsersRepository sut;
};

UsersRepositoryTest::UsersRepositoryTest()
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

    sut = UsersRepository();
}

UsersRepositoryTest::~UsersRepositoryTest()
{

}

void UsersRepositoryTest::initTestCase()
{
    string query = "create schema "+ m_schema + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}


void UsersRepositoryTest::init()
{
    string query = "create table if not exists "+ m_schema + ".Users\
                    (\
                        id serial primary key,\
                        login text,\
                        password text,\
                        role text,\
                        moderator_id int,\
                        FOREIGN KEY (moderator_id) REFERENCES PPO.Users (id)\
                    );\
                    alter table "+ m_schema + ".Users ADD constraint unique_login unique (login);";

    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());

    query = "insert into "+ m_schema + ".Users (login, password, role, moderator_id)\
                        values('user1', '123', 'canvas_user', NULL);\
            insert into "+ m_schema + ".Users (login, password, role, moderator_id)\
                        values('user2', '123', 'canvas_user', NULL);\
            insert into "+ m_schema + ".Users (login, password, role, moderator_id)\
                        values('moderator1', '123', 'moderator', NULL);\
            insert into "+ m_schema + ".Users (login, password, role, moderator_id)\
                        values('user3', '123', 'canvas_user', 3);";

    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

void UsersRepositoryTest::getUserByLoginPassTest()
{
    //ARRANGE in init()
    shared_ptr<UserBL> user, same_user;
    string login = "user1";
    string password = "123";

    //ACT
    try
    {
        user = sut.getUser(login, password);
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

    string query = "SELECT * FROM " + m_schema + ".Users where login='" + login + "' and password = '" + password + "';";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
    {
        int ID = q.value(0).toInt();
        string login = q.value(1).toString().toStdString();
        string password = q.value(2).toString().toStdString();
        string role = q.value(3).toString().toStdString();
        int moderator_id = q.value(4).toInt();

        same_user = make_shared<UserBL>(ID, login, password, role, moderator_id);
    }

    QVERIFY2(*user == *same_user, "getUserByLoginPassTest error");
}

void UsersRepositoryTest::getCanvasUserByNameTest()
{
    //ARRANGE in init()
    shared_ptr<UserBL> user, same_user;
    string name = "user1";

    //ACT
    try
    {
        user = sut.getCanvasUser(name);
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

    string query = "SELECT * FROM " + m_schema + ".Users where login='" + name + "' and role = 'canvas_user'";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
    {
        int ID = q.value(0).toInt();
        string login = q.value(1).toString().toStdString();
        string password = q.value(2).toString().toStdString();
        string role = q.value(3).toString().toStdString();
        int moderator_id = q.value(4).toInt();

        same_user = make_shared<UserBL>(ID, login, password, role, moderator_id);
    }

    QVERIFY2(*user == *same_user, "getCanvasUserByNameTest error");
}

void UsersRepositoryTest::getFreeCanvasUsersTest()
{
    //ARRANGE in init()
    vector<string> users, same_useres;

    //ACT
    try
    {
        users = sut.getFreeCanvasUsers();
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

    string query = "select login FROM " + m_schema + ".Users where role = 'canvas_user' and moderator_id is null;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    while (q.next())
    {
        string login = q.value(0).toString().toStdString();
        same_useres.push_back(login);
    }

    for (int i = 0; i < same_useres.size(); i++)
    {
        QString msg = QString("i = %1 users.login = %2; same_useres.login = %3;").
                arg(QString::number(i),QString::fromStdString(users[i]), QString::fromStdString(same_useres[i]));
        QVERIFY2(users[i] == same_useres[i], msg.toStdString().c_str());
    }
}

void UsersRepositoryTest::getCanvasUsersByMidTest()
{
    //ARRANGE in init()
    vector<string> users, same_useres;
    int moderator_id = 3;

    //ACT
    try
    {
        users = sut.getCanvasUsersByMid(moderator_id);
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

    string query = "select login FROM " + m_schema + ".Users where moderator_id = " + std::to_string(moderator_id) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    while (q.next())
    {
        string login = q.value(0).toString().toStdString();
        same_useres.push_back(login);
    }

    for (int i = 0; i < same_useres.size(); i++)
    {
        QString msg = QString("i = %1 users.login = %2; same_useres.login = %3;").
                arg(QString::number(i),QString::fromStdString(users[i]), QString::fromStdString(same_useres[i]));
        QVERIFY2(users[i] == same_useres[i], msg.toStdString().c_str());
    }
}

void UsersRepositoryTest::addUserTest()
{
    //ARRANGE in init()
    UserBL user = UserBL(-1, "user4", "123", "canvas_user", 3);
    shared_ptr<UserBL> same_user;
    int id = -1;

    //ACT
    try
    {
        id = sut.addUser(user);
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

    user = UserBL(id, user.getLogin(), user.getPassword(), user.getRole(), user.getModeratorId());
    string query = "SELECT * FROM " + m_schema + ".Users where id=" + std::to_string(id) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
    {
        int ID = q.value(0).toInt();
        string login = q.value(1).toString().toStdString();
        string password = q.value(2).toString().toStdString();
        string role = q.value(3).toString().toStdString();
        int moderator_id = q.value(4).toInt();

        same_user = make_shared<UserBL>(ID, login, password, role, moderator_id);
    }

    QVERIFY2(user == *same_user, "addUserTest error");
}

void UsersRepositoryTest::deleteUserTest()
{
    //ARRANGE в init()

    //ACT
    try
    {
        sut.deleteUser(1);
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

    string query = "SELECT * FROM " + m_schema + ".Users where id=" + to_string(1) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
        QFAIL("Canvas is not deleted");
}

void UsersRepositoryTest::updateUserTest()
{
    //ARRANGE
    UserBL user = UserBL(1, "user5", "456", "moderator", -1);
    shared_ptr<UserBL> same_user;

    //ACT
    try
    {
        sut.updateUser(user, 1);
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

    user = UserBL(user.getId(), user.getLogin(), user.getPassword(), user.getRole(), 0);
    string query = "SELECT * FROM " + m_schema + ".Users where id=" + to_string(1) + ";";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
    if (q.next())
    {
        int ID = q.value(0).toInt();
        string login = q.value(1).toString().toStdString();
        string password = q.value(2).toString().toStdString();
        string role = q.value(3).toString().toStdString();
        int moderator_id = q.value(4).toInt();

        same_user = make_shared<UserBL>(ID, login, password, role, moderator_id);
    }

    QVERIFY2(user == *same_user, "updateUserTest error");
}

void UsersRepositoryTest::cleanup()
{
    string query = "drop table " + m_schema + ".Users cascade;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

void UsersRepositoryTest::cleanupTestCase()
{
    string query = "drop schema " + m_schema + " cascade;";
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query)))
        QFAIL(q.lastError().text().toStdString().c_str());
}

QTEST_APPLESS_MAIN(UsersRepositoryTest)

#include "tst_usersrepositorytest.moc"
