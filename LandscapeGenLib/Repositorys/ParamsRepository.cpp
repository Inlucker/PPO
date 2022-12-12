#include "ParamsRepository.h"
#include "Settings.h"
#include "Errors/RepositoryErrors.h"

ParamsRepository::ParamsRepository()
{

}

shared_ptr<ParamsBL> ParamsRepository::getParams(int id)
{
    connect();
    string query = "SELECT * FROM " + m_schema + ".Params where canvas_id=" + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    int flag = 0;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int c_id = atoi(PQgetvalue (res, 0, 0));
            int width = atoi(PQgetvalue (res, 0, 1));
            int height = atoi(PQgetvalue (res, 0, 2));
            double range = atof(PQgetvalue (res, 0, 3));
            //qDebug(logInfo()) << PQgetvalue (res, 0, 4);
            bool smooth = PQgetvalue (res, 0, 4);
            //bool smooth = false;
            int mult = atoi(PQgetvalue (res, 0, 5));
            int red = atoi(PQgetvalue (res, 0, 6));
            int green = atoi(PQgetvalue (res, 0, 7));
            int blue = atoi(PQgetvalue (res, 0, 8));
            int size = atoi(PQgetvalue (res, 0, 9));

            return make_shared<ParamsBL>(c_id, width, height, range, smooth, mult, red, green, blue, size);
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
        throw GetParamsError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 1)
        throw GetParamsError("No such Params", __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetParamsError("Unexpected GetParamsError?", __FILE__, __LINE__, ctime(&t_time));
}

int ParamsRepository::addParams(ParamsBL &params)
{
    int id = -1;
    connect();
    int c_id = params.getCanvasID();
    int width = params.getWidth();
    int height = params.getHeight();
    double range = params.getRange();
    bool smooth = params.getSmooth();
    int mult = params.getMult();
    int red = params.getRed();
    int green = params.getGreen();
    int blue = params.getBlue();
    int size = params.getSize();

    string query = "insert into " + m_schema + ".Params values(";
    query += std::to_string(c_id) + ", ";
    query += std::to_string(width) + ", ";
    query += std::to_string(height) + ", ";
    query += std::to_string(range) + ", ";
    if (smooth)
        query += "TRUE, ";
    else
        query += "FALSE, ";
    //query += std::to_string(smooth) + ", ";
    query += std::to_string(mult) + ", ";
    query += std::to_string(red) + ", ";
    query += std::to_string(green) + ", ";
    query += std::to_string(blue) + ", ";
    query += std::to_string(size) + ")";
    query += "RETURNING canvas_id;";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        int rows_n = PQntuples(res);
        if (PQresultStatus(res) == PGRES_TUPLES_OK && rows_n)
            id = atoi(PQgetvalue (res, 0, 0));
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
        throw InsertParamsError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
    return id;
}

void ParamsRepository::deleteParams(int id)
{

    connect();
    string query = "delete from " + m_schema + ".Params where canvas_id=" + to_string(id) + ";";
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
        throw DeleteParamsError("No such params", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw DeleteParamsError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void ParamsRepository::updateParams(ParamsBL &params, int id)
{
    connect();
    //int c_id = params.getCanvasID();
    int width = params.getWidth();
    int height = params.getHeight();
    double range = params.getRange();
    bool smooth = params.getSmooth();
    int mult = params.getMult();
    int red = params.getRed();
    int green = params.getGreen();
    int blue = params.getBlue();
    int size = params.getSize();

    string query = "update " + m_schema + ".Params set width = " + to_string(width);
    query += ", height = " + to_string(height);
    query += ", range = " + to_string(range);
    query += ", smooth = ";
    if (smooth)
      query += "TRUE";
    else
      query += "FALSE";
    query += ", mult = " + to_string(mult);
    query += ", red = " + to_string(red);
    query += ", green = " + to_string(green);
    query += ", blue = " + to_string(blue);
    query += ", size = " + to_string(size);
    query += " where canvas_id = " + to_string(id) + ";";
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
        throw UpdateParamsError("No such params", __FILE__, __LINE__, ctime(&t_time));
    else if (flag == 2)
        throw UpdateParamsError(error_msg, __FILE__, __LINE__, ctime(&t_time));
}

void ParamsRepository::connect()
{

    string m_dbhost;
    int m_dbport;
    string m_dbname;
    string m_dbuser;
    string m_dbpass;
    m_dbhost = Settings::get(Settings::DBHost, Settings::DataBase).toString().toStdString();
    m_dbport = Settings::get(Settings::DBPort, Settings::DataBase).toInt();
    m_dbname = Settings::get(Settings::DBName, Settings::DataBase).toString().toStdString();
    m_dbuser = Settings::get(Settings::DBUser, Settings::DataBase).toString().toStdString();
    m_dbpass = Settings::get(Settings::DBPass, Settings::DataBase).toString().toStdString();
    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();

    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       time_t t_time = time(NULL);
       throw ConnectionError("m_connection", __FILE__, __LINE__, ctime(&t_time));
    }
}
