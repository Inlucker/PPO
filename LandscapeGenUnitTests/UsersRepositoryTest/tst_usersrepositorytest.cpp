#include <QtTest>
#include <QSqlQuery>
#include <QSqlError>

#define FILENAME "UsersRepositoryTest.cfg"

#include "Settings.h"
#include "Repositorys/UsersRepository.h"
#include "common.h"

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

    QString m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString();
    int m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    QString m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString();
    QString m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString();
    QString m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString();

    db = DataBaseBuilder::createPostgresDataBase(m_dbhost, m_dbport, m_dbname, m_dbuser, m_dbpass, m_schema);

    sut = UsersRepository();

    //int ver = PQlibVersion();
    //cout << ver << endl;
}

UsersRepositoryTest::~UsersRepositoryTest()
{

}

void UsersRepositoryTest::initTestCase()
{
    if (DataBaseBuilder::createSchema() != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
}


void UsersRepositoryTest::init()
{
    if (DataBaseBuilder::createUsersTable() != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());

    if (DataBaseBuilder::fillUsersTable() != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
}

void UsersRepositoryTest::getUserByLoginPassTest()
{
    //ARRANGE in init()
    shared_ptr<UserBL> user, user_exp;
    if (DataBaseBuilder::getUser(user_exp) != OK && !user_exp)
        QFAIL(DataBaseBuilder::lastError().c_str());
    string login = user_exp->getLogin();
    string password = user_exp->getPassword();

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

    QVERIFY2(*user == *user_exp, "getUserByLoginPassTest error");
}

void UsersRepositoryTest::getCanvasUserByNameTest()
{
    //ARRANGE in init()
    shared_ptr<UserBL> user, user_exp;
    int i = 1;
    do
    {
        if (DataBaseBuilder::getUser(user_exp, i++) != OK && !user_exp)
            QFAIL(DataBaseBuilder::lastError().c_str());
    } while (user_exp->getRole() != "canvas_user");

    string name = user_exp->getLogin();

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

    QVERIFY2(*user == *user_exp, "getCanvasUserByNameTest error");
}

void UsersRepositoryTest::getFreeCanvasUsersTest()
{
    //ARRANGE in init()
    vector<string> users, users_exp;
    vector<UserBL> vec;
    if (DataBaseBuilder::getFreeUsers(vec) != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
    for (const UserBL& u : vec)
        users_exp.push_back(u.getLogin());

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

    for (int i = 0; i < users_exp.size(); i++)
    {
        QString msg = QString("i = %1 users.login = %2; same_useres.login = %3;").
                arg(QString::number(i),QString::fromStdString(users[i]), QString::fromStdString(users_exp[i]));
        QVERIFY2(users[i] == users_exp[i], msg.toStdString().c_str());
    }
}

void UsersRepositoryTest::getCanvasUsersByMidTest()
{
    //ARRANGE in init()
    vector<string> users, users_exp;
    int moderator_id = 3;
    vector<UserBL> vec;
    if (DataBaseBuilder::getUsersByMid(vec, moderator_id) != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
    for (const UserBL& u : vec)
        users_exp.push_back(u.getLogin());

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

    for (int i = 0; i < users_exp.size(); i++)
    {
        QString msg = QString("i = %1 users.login = %2; same_useres.login = %3;").
                arg(QString::number(i),QString::fromStdString(users[i]), QString::fromStdString(users_exp[i]));
        QVERIFY2(users[i] == users_exp[i], msg.toStdString().c_str());
    }
}

void UsersRepositoryTest::addUserTest()
{
    //ARRANGE in init()
    UserBL user = UserBL(-1, "user4", "123", "canvas_user", 3);
    shared_ptr<UserBL> user_exp;
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
    if (DataBaseBuilder::getUser(user_exp, id) != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());

    QVERIFY2(user == *user_exp, "addUserTest error");
}

void UsersRepositoryTest::deleteUserTest()
{
    //ARRANGE в init()
    int id = 1;
    shared_ptr<UserBL> user_exp;

    //ACT
    try
    {
        sut.deleteUser(id);
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

    Status status = DataBaseBuilder::getUser(user_exp, id);
    if (status == EXEC_ERROR)
        QFAIL(DataBaseBuilder::lastError().c_str());
    if (status != EMPTY_RES)
        QFAIL("User is not deleted");
}

void UsersRepositoryTest::updateUserTest()
{
    //ARRANGE
    int id = 1;
    UserBL user = UserBL(id, "user5", "456", "moderator", -1);
    shared_ptr<UserBL> user_exp;

    //ACT
    try
    {
        sut.updateUser(user, id);
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
    if (DataBaseBuilder::getUser(user_exp, id) != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());

    QVERIFY2(user == *user_exp, "updateUserTest error");
}

void UsersRepositoryTest::cleanup()
{
    if (DataBaseBuilder::dropUsersTable() != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
}

void UsersRepositoryTest::cleanupTestCase()
{
    if (DataBaseBuilder::dropSchemaCascade() != OK)
        QFAIL(DataBaseBuilder::lastError().c_str());
}

QTEST_GUILESS_MAIN(UsersRepositoryTest)

#include "tst_usersrepositorytest.moc"
