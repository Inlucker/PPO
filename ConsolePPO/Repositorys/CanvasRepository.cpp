#include "CanvasRepository.h"

CanvasRepository::CanvasRepository() : m_dbhost("localhost"), m_dbport(5432), m_dbname("postgres"), m_dbuser("guest"), m_dbpass("guest"), m_dbschema("PPO")
{
    /*m_dbhost = "localhost";
    m_dbport = 5432;
    m_dbname = "postgres";
    m_dbuser = "canvas_user";
    m_dbpass = "canvas_user";
    m_dbschema = "PPO";*/
}

CanvasRepository::CanvasRepository(string dbuser, string dbpass, string dbschema, string dbhost, int dbport, string dbname)
    : m_dbhost(dbhost), m_dbport(dbport), m_dbname(dbname), m_dbuser(dbuser), m_dbpass(dbpass), m_dbschema(dbschema)
{

}

/*CanvasRepository::CanvasRepository(string dbhost, int dbport, string dbname, string dbuser, string dbpass, string dbschema)
{
    m_dbhost = dbhost;
    m_dbport = dbport;
    m_dbname = dbname;
    m_dbuser = dbuser;
    m_dbpass = dbpass;
    m_dbschema = dbschema;
}*/

/*CanvasRepository::~CanvasRepository()
{

}*/

shared_ptr<CanvasBL> CanvasRepository::getCanvas(int id)
{
    connect();
    string query = "SELECT * FROM " + m_dbschema + ".Canvas where id=" + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            //auto ID = PQgetvalue (res, 0, 0);
            int u_id = atoi(PQgetvalue (res, 0, 1));
            string name = PQgetvalue (res, 0, 2);
            string hm = PQgetvalue (res, 0, 3);
            string tpa = PQgetvalue (res, 0, 4);
            string c = PQgetvalue (res, 0, 5);
            //canvas = make_shared<CanvasBL>(hm, tpa, c);
            //return canvas;
            return make_shared<CanvasBL>(u_id, name, hm, tpa, c);
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

void CanvasRepository::addCanvas(CanvasBL &canvas)
{
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
    string query = "insert into " + m_dbschema + ".Canvas(user_id, name, HeightsMap, TriPolArray, Color) values(";
    query += u_id + ", '";
    query += name + "', '";
    query += hm + "', '";
    query += hmp + "', '";
    query += c + "');";
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
    }
    cout << error_msg;
    if (flag)
    {
        time_t t_time = time(NULL);
        throw InsertCanvasError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}

void CanvasRepository::deleteCanvas(int id)
{
    connect();
    string query = "delete from " + m_dbschema + ".Canvas where id=" + to_string(id) + ";";
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
    string query = "update " + m_dbschema + ".Canvas set HeightsMap = '" + hm;
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
            cout << PQresultErrorMessage(res) << endl;
        }

        PQclear( res );
    }
}

void CanvasRepository::setRole(string login, string password)
{
    m_dbuser = login;
    m_dbpass = password;
}

void CanvasRepository::connect()
{
    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       time_t t_time = time(NULL);
       throw ConnectionError("m_connection", __FILE__, __LINE__, ctime(&t_time));
    }
}
