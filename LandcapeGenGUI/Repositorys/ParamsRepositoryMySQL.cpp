#include "ParamsRepositoryMySQL.h"
#include "Settings.h"
#include <QSqlQuery>
#include <QSqlError>

ParamsRepositoryMySQL::ParamsRepositoryMySQL()
{
    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();
}

shared_ptr<ParamsBL> ParamsRepositoryMySQL::getParams(int id)
{
    string query = "SELECT * FROM " + m_schema + ".Params where canvas_id=" + to_string(id) + ";";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.next())
    {
        int c_id = q.value(0).toInt();
        int width = q.value(1).toInt();
        int height = q.value(2).toInt();
        int range = q.value(3).toInt();
        bool smooth = q.value(4).toBool();
        int mult = q.value(5).toInt();
        int red = q.value(6).toInt();
        int green = q.value(7).toInt();
        int blue = q.value(8).toInt();
        int size = q.value(9).toInt();

        return make_shared<ParamsBL>(c_id, width, height, range, smooth, mult, red, green, blue, size);
    }
    else
    {
        time_t t_time = time(NULL);
        throw GetParamsError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

void ParamsRepositoryMySQL::addParams(ParamsBL &params)
{

    int c_id = params.getCanvasID();
    int width = params.getWidth();
    int height = params.getHeight();
    int range = params.getRange();
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
    query += std::to_string(smooth) + ", ";
    query += std::to_string(mult) + ", ";
    query += std::to_string(red) + ", ";
    query += std::to_string(green) + ", ";
    query += std::to_string(blue) + ", ";
    query += std::to_string(size) + ");";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            //OK
        }
    else
    {
        time_t t_time = time(NULL);
        throw InsertParamsError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

void ParamsRepositoryMySQL::deleteParams(int id)
{
    string query = "delete from " + m_schema + ".Params where canvas_id=" + to_string(id) + ";";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            //OK
        }
    else
    {
        time_t t_time = time(NULL);
        throw DeleteParamsError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

void ParamsRepositoryMySQL::updateParams(ParamsBL &params, int id)
{
    int width = params.getWidth();
    int height = params.getHeight();
    int range = params.getRange();
    bool smooth = params.getSmooth();
    int mult = params.getMult();
    int red = params.getRed();
    int green = params.getGreen();
    int blue = params.getBlue();
    int size = params.getSize();

    string query = "update " + m_schema + ".Params set width = " + to_string(width);
    query += ", height = " + to_string(height);
    query += ", rang = " + to_string(range);
    query += ", smooth = " + to_string(smooth);
    query += ", mult = " + to_string(mult);
    query += ", red = " + to_string(red);
    query += ", green = " + to_string(green);
    query += ", blue = " + to_string(blue);
    query += ", size = " + to_string(size);
    query += " where id = " + to_string(id) + ";";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            //OK
        }
    else
    {
        time_t t_time = time(NULL);
        throw UpdateParamsError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}
