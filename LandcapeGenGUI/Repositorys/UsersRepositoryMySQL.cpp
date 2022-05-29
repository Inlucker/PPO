#include "UsersRepositoryMySQL.h"
#include "Settings.h"
#include <QSqlQuery>
#include <QSqlError>

//#include <iostream>
//using namespace std;

UsersRepositoryMySQL::UsersRepositoryMySQL()
{
    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();
}

shared_ptr<UserBL> UsersRepositoryMySQL::getUser(string login, string password)
{
    string query = "SELECT * FROM " + m_schema + ".Users where login='" + login + "' and password = '" + password + "';";
    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.next())
    {
        int ID = q.value(0).toInt();
        string login = q.value(1).toString().toStdString();
        string password = q.value(2).toString().toStdString();
        string role = q.value(3).toString().toStdString();
        int moderator_id = q.value(4).toInt();

        return make_shared<UserBL>(ID, login, password, role, moderator_id);
    }
    else
    {
        time_t t_time = time(NULL);
        throw LoginError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

shared_ptr<UserBL> UsersRepositoryMySQL::getCanvasUser(string name)
{
    string query = "SELECT * FROM " + m_schema + ".Users where login='" + name + "';";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.next())
    {
        int ID = q.value(0).toInt();
        string login = q.value(1).toString().toStdString();
        string password = q.value(2).toString().toStdString();
        string role = q.value(3).toString().toStdString();
        int moderator_id = q.value(4).toInt();

        return make_shared<UserBL>(ID, login, password, role, moderator_id);
    }
    else
    {
        time_t t_time = time(NULL);
        throw GetUsersError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

vector<string> UsersRepositoryMySQL::getFreeCanvasUsers()
{
    string query = "select login FROM PPO.Users where role = 'canvas_user' and moderator_id is null;";

    vector<string> vec;

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            string login = q.value(0).toString().toStdString();
            vec.push_back(login);
        }
    else
    {
        time_t t_time = time(NULL);
        throw GetUsersError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }

    return vec;
}

vector<string> UsersRepositoryMySQL::getCanvasUsersByMid(int m_id)
{
    string query = "select login FROM PPO.Users where moderator_id = " + std::to_string(m_id) + ";";
    vector<string> vec;

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            string login = q.value(0).toString().toStdString();
            vec.push_back(login);
        }
    else
    {
        time_t t_time = time(NULL);
        throw GetUsersError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }

    return vec;
}

void UsersRepositoryMySQL::addUser(UserBL &user_bl)
{
    string login = user_bl.getLogin();
    string password = user_bl.getPassword();
    string role = user_bl.getRole();

    string query = "insert into " + m_schema + ".Users(login, password, role, moderator_id) values('";
    //string query = "insert into " + m_dbschema + ".Canvas values(-1, 1, 'CanvasName', '";
    query += login + "', '";
    query += password + "', '";
    query += role + "', NULL);";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            //OK?
        }
    else
    {
        time_t t_time = time(NULL);
        throw RegistrateUserError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

void UsersRepositoryMySQL::deleteUser(int id)
{
    string query = "delete from " + m_schema + ".Users where id=" + to_string(id) + ";";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            //OK?
        }
    else
    {
        time_t t_time = time(NULL);
        throw DeleteUserError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

void UsersRepositoryMySQL::updateUser(UserBL &user_bl, int id)
{
    string login, password, role, m_id;
    login = user_bl.getLogin();
    password = user_bl.getPassword();
    role = user_bl.getRole();
    if (user_bl.getModeratorId() == -1)
        m_id = "NULL";
    else
        m_id = "'" + std::to_string(user_bl.getModeratorId()) + "'";
    string query = "update " + m_schema + ".Users set login = '" + login;
    query += "', password = '" + password;
    query += "', role = '" + role;
    query += "', moderator_id = " + m_id;
    query += " where id = " + to_string(id) + ";";


    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            //OK?
        }
    else
    {
        time_t t_time = time(NULL);
        throw UpdateUserError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}
