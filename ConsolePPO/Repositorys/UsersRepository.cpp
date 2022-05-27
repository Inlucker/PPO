#include "UsersRepository.h"

UsersRepository::UsersRepository() : m_dbhost("localhost"), m_dbport(5432), m_dbname("postgres"), m_dbuser("moderator"), m_dbpass("moderator"), m_dbschema("PPO")
{

}

UsersRepository::UsersRepository(string dbuser, string dbpass, string dbschema, string dbhost, int dbport, string dbname)
    : m_dbhost(dbhost), m_dbport(dbport), m_dbname(dbname), m_dbuser(dbuser), m_dbpass(dbpass), m_dbschema(dbschema)
{

}

shared_ptr<UserBL> UsersRepository::getUser(string login, string password)
{
    connect();
    string query = "SELECT * FROM " + m_dbschema + ".Users where login='" + login + "' and password = '" + password + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            string login = PQgetvalue (res, 0, 1);
            string password = PQgetvalue (res, 0, 2);
            string role = PQgetvalue (res, 0, 3);
            int moderator_id = atoi(PQgetvalue (res, 0, 4));

            return make_shared<UserBL>(ID, login, password, role, moderator_id);
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag)
        throw LoginError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw LoginError("login or password", __FILE__, __LINE__, ctime(&t_time));
    //return NULL;
}

shared_ptr<UserBL> UsersRepository::getCanvasUser(string name)
{
    connect();
    string query = "SELECT * FROM " + m_dbschema + ".Users where login='" + name + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            string login = PQgetvalue (res, 0, 1);
            string password = PQgetvalue (res, 0, 2);
            string role = PQgetvalue (res, 0, 3);
            int moderator_id = atoi(PQgetvalue (res, 0, 4));

            return make_shared<UserBL>(ID, login, password, role, moderator_id);
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag)
        throw GetUsersError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetUsersError("Get canvas_user", __FILE__, __LINE__, ctime(&t_time));
}

vector<string> UsersRepository::getFreeCanvasUsers()
{
    connect();
    string query = "select login FROM PPO.Users where role = 'canvas_user' and moderator_id is null;";
    PQsendQuery(m_connection.get(), query.c_str());

    vector<string> vec;
    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        int rows_n = PQntuples(res);
        if (PQresultStatus(res) == PGRES_TUPLES_OK && rows_n)
        {
            for (int i = 0; i < rows_n; i++)
            {
                string login = PQgetvalue (res, i, 0);
                vec.push_back(login);
            }
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag)
        throw GetUsersError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

vector<string> UsersRepository::getCanvasUsersByMid(int m_id)
{
    connect();
    string query = "select login FROM PPO.Users where moderator_id = " + std::to_string(m_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    vector<string> vec;
    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        int rows_n = PQntuples(res);
        if (PQresultStatus(res) == PGRES_TUPLES_OK && rows_n)
        {
            for (int i = 0; i < rows_n; i++)
            {
                string login = PQgetvalue (res, i, 0);
                vec.push_back(login);
            }
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag)
        throw GetUsersError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

void UsersRepository::addUser(UserBL &user)
{
    connect();
    string login = user.getLogin();
    string password = user.getPassword();
    string role = user.getRole();

    string query = "insert into " + m_dbschema + ".Users(login, password, role, moderator_id) values('";
    //string query = "insert into " + m_dbschema + ".Canvas values(-1, 1, 'CanvasName', '";
    query += login + "', '";
    query += password + "', '";
    query += role + "', NULL);";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    if (flag)
    {
        time_t t_time = time(NULL);
        throw RegistrateUserError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}

void UsersRepository::deleteUser(int id)
{
    connect();
    string query = "delete from " + m_dbschema + ".Users where id=" + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQcmdTuples(res)[0] == '0')
            flag = true;
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = 2;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag == 1)
        throw DeleteUserError("No such user", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw DeleteUserError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void UsersRepository::updateUser(UserBL &user_bl, int id)
{
    connect();
    //string query = "update login FROM PPO.Users where id = " + std::to_string(id) + ";";

    string login, password, role, m_id;
    login = user_bl.getLogin();
    password = user_bl.getPassword();
    role = user_bl.getRole();
    if (user_bl.getModeratorId() == -1)
        m_id = "NULL";
    else
        m_id = "'" + std::to_string(user_bl.getModeratorId()) + "'";
    string query = "update " + m_dbschema + ".Users set login = '" + login;
    query += "', password = '" + password;
    query += "', role = '" + role;
    query += "', moderator_id = " + m_id;
    query += " where id = " + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQcmdTuples(res)[0] == '0')
            flag = 1;
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = 2;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag == 1)
        throw UpdateUserError("No such user", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw UpdateUserError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void UsersRepository::connect()
{
    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       time_t t_time = time(NULL);
       throw ConnectionError("m_connection", __FILE__, __LINE__, ctime(&t_time));
    }
}
