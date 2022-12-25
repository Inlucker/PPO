#include "CanvasRepository.h"
#include "../Settings.h"

/*CanvasRepository::CanvasRepository()
{

}*/

CanvasRepository::CanvasRepository(string dbuser, string dbpass, string dbschema, string dbhost, int dbport, string dbname)
{
  m_dbhost = dbhost;
  m_dbport = dbport;
  m_dbname = dbname;
  m_dbuser = dbuser;
  m_dbpass = dbpass;
  m_schema = dbschema;
}

shared_ptr<CanvasBL> CanvasRepository::getCanvas(int id)
{
    connect();
    string query = "SELECT * FROM " + m_schema + ".Canvas where id=" + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            int u_id = atoi(PQgetvalue (res, 0, 1));
            string name = PQgetvalue (res, 0, 2);
            string hm = PQgetvalue (res, 0, 3);
            string tpa = PQgetvalue (res, 0, 4);
            string c = PQgetvalue (res, 0, 5);
            //canvas = make_shared<CanvasBL>(hm, tpa, c);
            //return canvas;
            return make_shared<CanvasBL>(ID, u_id, name, hm, tpa, c);
            //cout<< ID<<endl;
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = 2;
        }
        else
            flag = 1;

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag == 2)
        throw GetCanvasError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 1)
        throw GetCanvasError("No such Canvas", __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetCanvasError("Unexpected GetCanvasError error?", __FILE__, __LINE__, ctime(&t_time));
    //return NULL;
}

shared_ptr<CanvasBL> CanvasRepository::getCanvas(string name)
{
    connect();
    string query = "SELECT * FROM " + m_schema + ".Canvas where name='" + name + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            int u_id = atoi(PQgetvalue (res, 0, 1));
            string name = PQgetvalue (res, 0, 2);
            string hm = PQgetvalue (res, 0, 3);
            string tpa = PQgetvalue (res, 0, 4);
            string c = PQgetvalue (res, 0, 5);
            //canvas = make_shared<CanvasBL>(hm, tpa, c);
            //return canvas;
            return make_shared<CanvasBL>(ID, u_id, name, hm, tpa, c);
            //cout<< ID<<endl;
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = 2;
        }
        else
            flag = 1;

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag == 2)
        throw GetCanvasError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 1)
        throw GetCanvasError("No such Canvas", __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetCanvasError("Unexpected GetCanvasError error?", __FILE__, __LINE__, ctime(&t_time));
}

vector<pair<int, string> > CanvasRepository::getCanvasesByUid(int u_id)
{
    connect();
    string query = "select id, name FROM PPO.Canvas where user_id = " + std::to_string(u_id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    vector<pair<int, string>> vec;
    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        int rows_n = PQntuples(res);
        if (PQresultStatus(res) == PGRES_TUPLES_OK && rows_n)
        {
            for (int i = 0; i < rows_n; i++)
            {
                int c_id = atoi(PQgetvalue (res, i, 0));
                string name = PQgetvalue (res, i, 1);
                vec.push_back(make_pair(c_id, name));
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
        throw GetCanvasError(error_msg, __FILE__, __LINE__, ctime(&t_time));

    return vec;
}

int CanvasRepository::addCanvas(CanvasBL &canvas)
{
    int id = -1;
    connect();
    string u_id = std::to_string(canvas.getUserId());
    string name = canvas.getName();
    string tmp;
    canvas.getHeightsMap().toStr(tmp);
    string hm = tmp;
    canvas.getHeightsMapPoints().toStr(tmp);
    string hmp = tmp;
    int r, g, b;
    canvas.getColor(r, g, b);
    string c = to_string(r) + " " + to_string(g) + " " + to_string(b);

    //string query = "insert into " + m_dbschema + ".Canvas(user_id, name, HeightsMap, TriPolArray, Color) values(1, 'CanvasName', '";
    string query = "insert into " + m_schema + ".Canvas(user_id, name, HeightsMap, TriPolArray, Color) values(";
    query += u_id + ", '";
    query += name + "', '";
    query += hm + "', '";
    query += hmp + "', '";
    query += c + "')";
    query += "RETURNING id;";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        int rows_n = PQntuples(res);
        if (PQresultStatus(res) == PGRES_TUPLES_OK && rows_n)
            id = atoi(PQgetvalue(res, 0, 0));
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }
    }
    //cout << error_msg;
    if (flag)
    {
        time_t t_time = time(NULL);
        throw InsertCanvasError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
    return id;
}

void CanvasRepository::deleteCanvas(int id)
{
    connect();
    string query = "delete from " + m_schema + ".Canvas where id=" + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQcmdTuples(res)[0] == '0')
            flag = 1;
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = 2;
        }
    }

    time_t t_time = time(NULL);
    if (flag == 1)
        throw DeleteCanvasError("No such canvas", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw DeleteCanvasError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void CanvasRepository::updateCanvas(CanvasBL &canvas_bl, int id)
{
    connect();
    string hm, hmp, c;
    canvas_bl.getHeightsMap().toStr(hm);
    canvas_bl.getHeightsMapPoints().toStr(hmp);
    canvas_bl.getColor(c);
    string query = "update " + m_schema + ".Canvas set Name = '" + canvas_bl.getName();
    query += "', HeightsMap = '" + hm;
    query += "', TriPolArray = '" + hmp;
    query += "', Color = '" + c;
    query += "' where id = " + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQcmdTuples(res)[0] == '0')
            flag = 1;
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = 2;
        }
    }

    time_t t_time = time(NULL);
    if (flag == 1)
        throw UpdateCanvasError("No such canvas\nMaybe you should create it first", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw UpdateCanvasError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void CanvasRepository::test(string &str)
{
    connect();
    str = "";
    string query = "SELECT current_user, session_user;";
    PQsendQuery(m_connection.get(), query.c_str());

    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            str += PQgetvalue(res, 0, 0);
            str += "; ";
            str += PQgetvalue(res, 0, 1);
        }
        else //if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            str = "TEST ERROR";
            //cout << PQresultErrorMessage(res) << endl;
        }

        PQclear( res );
    }
}

void CanvasRepository::connect()
{
    /*string m_dbhost;
    int m_dbport;
    string m_dbname;
    string m_dbuser;
    string m_dbpass;
    m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString().toStdString();
    m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString().toStdString();
    m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString().toStdString();
    m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString().toStdString();
    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();*/

    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
        string error_msg = PQerrorMessage(m_connection.get());
        time_t t_time = time(NULL);
        throw ConnectionError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}
