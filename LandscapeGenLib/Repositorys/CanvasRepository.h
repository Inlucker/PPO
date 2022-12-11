#ifndef CANVASREPOSITORY_H
#define CANVASREPOSITORY_H

#include <memory>
#include <libpq-fe.h>
#include <vector>
//#include <pair>

#include "ICanvasRepository.h"
#include "Errors/RepositoryErrors.h"

class CanvasRepository : public ICanvasRepository
{
public:
    CanvasRepository();
    //CanvasRepository(string dbuser, string dbpass, string dbschema = "PPO", string dbhost = "localhost", int dbport = 5432, string dbname = "postgres");
    virtual ~CanvasRepository() = default;

    virtual shared_ptr<CanvasBL> getCanvas(int id) override;
    shared_ptr<CanvasBL> getCanvas(string name);
    vector<pair<int, string>> getCanvasesByUid(int u_id);
    virtual void addCanvas(CanvasBL& canvas) override;
    virtual void deleteCanvas(int id) override;
    virtual void updateCanvas(CanvasBL& canvas_bl, int id) override;

    void test(string &str);

protected:
    void connect();

    /*string m_dbhost;
    int m_dbport;
    string m_dbname;
    string m_dbuser;
    string m_dbpass;*/
    string m_schema;

    shared_ptr<PGconn> m_connection;
};

#endif // CANVASREPOSITORY_H
