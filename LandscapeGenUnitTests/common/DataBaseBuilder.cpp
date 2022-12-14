#include "DataBaseBuilder.h"
//#include "CanvasMother.h"

string DataBaseBuilder::m_schema = "";
QSqlQuery DataBaseBuilder::m_query = QSqlQuery();
string DataBaseBuilder::m_last_error = "No errors";

void DataBaseBuilder::setSchema(string schema)
{
    m_schema = schema;
}

unique_ptr<QSqlDatabase> DataBaseBuilder::createPostgresDataBase(QString dbhost, int dbport, QString dbname, QString dbuser, QString dbpass, string schema)
{
    string test = m_schema;
    unique_ptr<QSqlDatabase> db = make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QPSQL"));

    db->setHostName(dbhost);
    db->setPort(dbport);
    db->setDatabaseName(dbname);
    db->setUserName(dbuser);
    db->setPassword(dbpass);
    m_schema = schema;

    if (!db->open())
    {
        m_last_error = db->lastError().text().toStdString().c_str();
        qDebug() << db->lastError().text();
    }
    else
        m_query = QSqlQuery("", *db);

    return db;
}

Status DataBaseBuilder::createSchema(string schema)
{
    string query = "create schema "+ schema + ";";
    return execQuery(query);
}

Status DataBaseBuilder::dropSchemaCascade(string schema)
{
    string query = "drop schema " + schema + " cascade;";
    return execQuery(query);
}

Status DataBaseBuilder::createCanvasTable(string schema)
{
    string query = "create table if not exists "+ schema + ".Canvas\
            (\
                id serial primary key,\
                user_id int,\
                name text,\
                HeightsMap text,\
                TriPolArray text,\
                Color text\
            );";

    return execQuery(query);
}

Status DataBaseBuilder::insertCanvasTable(CanvasBL &canvas, string schema)
{
    string u_id = std::to_string(canvas.getUserId());
    string name = canvas.getName();
    string tmp;
    canvas.getHeightsMap().toStr(tmp);
    string hm_str = tmp;
    canvas.getHeightsMapPoints().toStr(tmp);
    string hmp = tmp;
    int r, g, b;
    canvas.getColor(r, g, b);
    string c = to_string(r) + " " + to_string(g) + " " + to_string(b);

    string query = "insert into " + schema + ".Canvas(user_id, name, HeightsMap, TriPolArray, Color) values(";
    query += u_id + ", '";
    query += name + "', '";
    query += hm_str + "', '";
    query += hmp + "', '";
    query += c + "');";

    return execQuery(query);
}

Status DataBaseBuilder::fillCanvasTable(int n, string schema)
{
    string query = "";
    int size = 33;
    for (int i = 0; i < n; i++)
    {
        shared_ptr<CanvasBL> canvas = CanvasMother::withSize(size);
        /*HeightsMap hm = HeightsMap(size);
        hm.diamondSquare();
        shared_ptr<CanvasBL> canvas = make_shared<CanvasBL>(1, 1, "CanvasName", hm, *hm.createPoints(), 20, 150, 20);*/

        string u_id = std::to_string(canvas->getUserId());
        string name = canvas->getName();
        string tmp;
        canvas->getHeightsMap().toStr(tmp);
        string hm_str = tmp;
        canvas->getHeightsMapPoints().toStr(tmp);
        string hmp = tmp;
        int r, g, b;
        canvas->getColor(r, g, b);
        string c = to_string(r) + " " + to_string(g) + " " + to_string(b);

        query += "insert into " + schema + ".Canvas(user_id, name, HeightsMap, TriPolArray, Color) values(";
        query += u_id + ", '";
        query += name + "', '";
        query += hm_str + "', '";
        query += hmp + "', '";
        query += c + "');\n";

        //insertCanvasTable(canvas, schema);
    }

    return execQuery(query);
}

Status DataBaseBuilder::dropCanvasTable(string schema)
{
    string query = "drop table " + schema + ".Canvas cascade;";
    return execQuery(query);
}

Status DataBaseBuilder::getCanvas(shared_ptr<CanvasBL> &canvas, int id, string schema)
{
    string query = "SELECT * FROM " + m_schema + ".Canvas where id =" + to_string(id) + ";";
    if (execQuery(query) == EXEC_ERROR)
        return EXEC_ERROR;
    //QFAIL(m_query.lastError().text());
    shared_ptr<CanvasBL> same_canvas;
    if (m_query.next())
    {
        int id = m_query.value(0).toInt();
        int u_id = m_query.value(1).toInt();
        string name = m_query.value(2).toString().toStdString();
        string hm = m_query.value(3).toString().toStdString();
        string tpa = m_query.value(4).toString().toStdString();
        string c = m_query.value(5).toString().toStdString();

        canvas = make_shared<CanvasBL>(id, u_id, name, hm, tpa, c);
    }
    else
    {
        m_last_error = "No canvas with id = " + to_string(id);
        return EMPTY_RES;
    }
    return OK;
}

Status DataBaseBuilder::getCanvasesByUid(vector<CanvasBL> &canvases, int user_id, string schema)
{
    string query = "SELECT * FROM " + m_schema + ".Canvas where user_id = " + std::to_string(user_id) + ";";
    if (execQuery(query) == EXEC_ERROR)
        return EXEC_ERROR;
    canvases.clear();
    while (m_query.next())
    {
        int id = m_query.value(0).toInt();
        int u_id = m_query.value(1).toInt();
        string name = m_query.value(2).toString().toStdString();
        string hm = m_query.value(3).toString().toStdString();
        string tpa = m_query.value(4).toString().toStdString();
        string c = m_query.value(5).toString().toStdString();

        canvases.push_back(CanvasBL(id, u_id, name, hm, tpa, c));
    }
    if (canvases.size() == 0)
    {
        m_last_error = "No canvases with user_id = " + to_string(user_id);
        return EMPTY_RES;
    }
    return OK;
}

Status DataBaseBuilder::createUsersTable(string schema)
{
    string query = "create table if not exists "+ schema + ".Users\
            (\
                id serial primary key,\
                login text,\
                password text,\
                role text,\
                moderator_id int,\
                FOREIGN KEY (moderator_id) REFERENCES "+ schema + ".Users (id)\
            );\
            alter table "+ schema + ".Users ADD constraint unique_login unique (login);";

    return execQuery(query);
}

Status DataBaseBuilder::fillUsersTable(string schema)
{
    string query = "insert into "+ schema + ".Users (login, password, role, moderator_id)\
                                values('user1', '123', 'canvas_user', NULL);\
                    insert into "+ schema + ".Users (login, password, role, moderator_id)\
                                values('user2', '123', 'canvas_user', NULL);\
                    insert into "+ schema + ".Users (login, password, role, moderator_id)\
                                values('moderator1', '123', 'moderator', NULL);\
                    insert into "+ schema + ".Users (login, password, role, moderator_id)\
                                values('user3', '123', 'canvas_user', 3);";

                    return execQuery(query);
}

Status DataBaseBuilder::dropUsersTable(string schema)
{
    string query = "drop table " + m_schema + ".Users cascade;";
    return execQuery(query);
}

Status DataBaseBuilder::getUser(shared_ptr<UserBL> &user, int id, string schema)
{
    string query = "SELECT * FROM " + m_schema + ".Users where id=" + to_string(id) + ";";
    if (execQuery(query) == EXEC_ERROR)
        return EXEC_ERROR;
    if (m_query.next())
    {
        int ID = m_query.value(0).toInt();
        string login = m_query.value(1).toString().toStdString();
        string password = m_query.value(2).toString().toStdString();
        string role = m_query.value(3).toString().toStdString();
        int moderator_id = m_query.value(4).toInt();

        user = make_shared<UserBL>(ID, login, password, role, moderator_id);
    }
    else
    {
        m_last_error = "No user with id = " + to_string(id);
        return EMPTY_RES;
    }
    return OK;
}

Status DataBaseBuilder::getFreeUsers(vector<UserBL> &users, string schema)
{
    string query = "select * FROM " + m_schema + ".Users where role = 'canvas_user' and moderator_id is null;";
    if (execQuery(query) == EXEC_ERROR)
        return EXEC_ERROR;
    users = getUsersFromQuery();
    if (users.size() == 0)
    {
        m_last_error = "No free";
        return EMPTY_RES;
    }
    return OK;
}

Status DataBaseBuilder::getUsersByMid(vector<UserBL> &users, int moderator_id, string schema)
{
    string query = "select * FROM " + m_schema + ".Users where moderator_id = " + std::to_string(moderator_id) + ";";
    if (execQuery(query) == EXEC_ERROR)
        return EXEC_ERROR;
    users = getUsersFromQuery();
    if (users.size() == 0)
    {
        m_last_error = "No free";
        return EMPTY_RES;
    }
    return OK;
}

QSqlQuery DataBaseBuilder::getQSqlQuery()
{
    return m_query;
}

string DataBaseBuilder::lastError()
{
    return m_last_error;
}

inline Status DataBaseBuilder::execQuery(string query)
{
    if (!m_query.exec(QString::fromStdString(query)))
    {
        m_last_error = m_query.lastError().text().toStdString();
        return EXEC_ERROR;
    }
    return OK;
}

vector<UserBL> DataBaseBuilder::getUsersFromQuery()
{
    vector<UserBL> users;
    while (m_query.next())
    {
        int ID = m_query.value(0).toInt();
        string login = m_query.value(1).toString().toStdString();
        string password = m_query.value(2).toString().toStdString();
        string role = m_query.value(3).toString().toStdString();
        int moderator_id = m_query.value(4).toInt();

        users.push_back(UserBL(ID, login, password, role, moderator_id));
    }
    return users;
}
