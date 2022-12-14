#ifndef DATABASEBUILDER_H
#define DATABASEBUILDER_H

#include <QSqlQuery>
#include <QSqlError>
#include <memory>
#include <QDebug>

using namespace std;

#include "Essensities/CanvasBL.h"
#include "Essensities/UserBL.h"

enum Status
{
    OK = 0,
    EXEC_ERROR = 1,
    EMPTY_RES = 2
};

class DataBaseBuilder
{
public:
    DataBaseBuilder() = delete;

    static void setSchema(string schema);
    static unique_ptr<QSqlDatabase> createPostgresDataBase(QString dbhost, int dbport, QString dbname, QString dbuser, QString dbpass, string schema);
    static Status createSchema(string schema = m_schema);
    static Status dropSchemaCascade(string schema = m_schema);

    //Canvas
    static Status createCanvasTable(string schema = m_schema);
    static Status insertCanvasTable(CanvasBL &canvas, string schema = m_schema);
    static Status fillCanvasTable(int n = 5, string schema = m_schema);
    static Status dropCanvasTable(string schema = m_schema);
    static Status getCanvas(shared_ptr<CanvasBL> &canvas, int id = 1, string schema = m_schema);
    static Status getCanvasesByUid(vector<CanvasBL> &canvases, int u_id = 1, string schema = m_schema);

    //Users
    static Status createUsersTable(string schema = m_schema);
    static Status fillUsersTable(string schema = m_schema);
    static Status dropUsersTable(string schema = m_schema);
    static Status getUser(shared_ptr<UserBL> &user, int id = 1, string schema = m_schema);
    static Status getFreeUsers(vector<UserBL> &users, string schema = m_schema);
    static Status getUsersByMid(vector<UserBL> &users, int moderator_id, string schema = m_schema);

    static QSqlQuery getQSqlQuery();
    static string lastError();

private:
    static inline Status execQuery(string query);
    static vector<UserBL> getUsersFromQuery();

private:
    static string m_schema;
    static QSqlQuery m_query;
    static string m_last_error;
};

#endif //DATABASEBUILDER_H
