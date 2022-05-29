#include "CanvasRepositoryMySQL.h"
#include "Settings.h"
#include <QSqlQuery>
#include <QSqlError>

CanvasRepositoryMySQL::CanvasRepositoryMySQL()
{
    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();
}

shared_ptr<CanvasBL> CanvasRepositoryMySQL::getCanvas(int id)
{
    string query = "SELECT * FROM " + m_schema + ".Canvas where id=" + to_string(id) + ";";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.next())
    {
        int id = q.value(0).toInt();
        int u_id = q.value(1).toInt();
        string name = q.value(2).toString().toStdString();
        string hm = q.value(3).toString().toStdString();
        string tpa = q.value(4).toString().toStdString();
        string c = q.value(5).toString().toStdString();

        return make_shared<CanvasBL>(id, u_id, name, hm, tpa, c);
    }
    else
    {
        time_t t_time = time(NULL);
        throw GetCanvasError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

shared_ptr<CanvasBL> CanvasRepositoryMySQL::getCanvas(string name)
{
    string query = "SELECT * FROM " + m_schema + ".Canvas where name='" + name + "';";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.next())
    {
        int id = q.value(0).toInt();
        int u_id = q.value(1).toInt();
        string name = q.value(2).toString().toStdString();
        string hm = q.value(3).toString().toStdString();
        string tpa = q.value(4).toString().toStdString();
        string c = q.value(5).toString().toStdString();

        return make_shared<CanvasBL>(id, u_id, name, hm, tpa, c);
    }
    else
    {
        time_t t_time = time(NULL);
        throw GetCanvasError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

vector<pair<int, string> > CanvasRepositoryMySQL::getCanvasesByUid(int u_id)
{
    string query = "select id, name FROM PPO.Canvas where user_id = " + std::to_string(u_id) + ";";

    vector<pair<int, string>> vec;
    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            int c_id = q.value(0).toInt();
            string name = q.value(1).toString().toStdString();
            vec.push_back(make_pair(c_id, name));
        }
    else
    {
        time_t t_time = time(NULL);
        throw GetCanvasError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
    return vec;
}

void CanvasRepositoryMySQL::addCanvas(CanvasBL &canvas)
{
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
    query += c + "');";

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
        throw InsertCanvasError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

void CanvasRepositoryMySQL::deleteCanvas(int id)
{
    string query = "delete from " + m_schema + ".Canvas where id=" + to_string(id) + ";";

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
        throw DeleteCanvasError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

void CanvasRepositoryMySQL::updateCanvas(CanvasBL &canvas_bl, int id)
{
    string hm, hmp, c;
    canvas_bl.getHeightsMap().toStr(hm);
    canvas_bl.getHeightsMapPoints().toStr(hmp);
    canvas_bl.getColor(c);
    string query = "update " + m_schema + ".Canvas set HeightsMap = '" + hm;
    query += "', TriPolArray = '" + hmp;
    query += "', Color = '" + c;
    query += "' where id = " + to_string(id) + ";";

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
        throw UpdateCanvasError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

void CanvasRepositoryMySQL::test(string &str)
{
    str = "";
    string query = "SELECT current_user();";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.isActive())
        while (q.next())
        {
            str += q.value(0).toString().toStdString();
        }
    else
    {
        str = "TEST ERROR";
    }
}
