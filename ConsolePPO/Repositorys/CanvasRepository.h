#ifndef CANVASREPOSITORY_H
#define CANVASREPOSITORY_H

#include <memory>
#include <libpq-fe.h>

#include "ICanvasRepository.h"
#include "Errors/RepositoryErrors.h"

class CanvasRepository : public ICanvasRepository
{
public:
    CanvasRepository();
    CanvasRepository(string dbuser, string dbpass, string dbschema = "PPO", string dbhost = "localhost", int dbport = 5432, string dbname = "postgres");
    virtual ~CanvasRepository() = default;

    virtual shared_ptr<CanvasBL> getCanvas(int id) override;
    virtual void addCanvas(CanvasBL& canvas) override;
    virtual void deleteCanvas(int id) override;
    virtual void updateCanvas(CanvasBL& canvas_bl, int id) override;

    void test(string &str);
    void setRole(string login, string password);

protected:
    void connect();

//private:
    string m_dbhost;
    int m_dbport;
    string m_dbname;
    string m_dbuser;
    string m_dbpass;
    string m_dbschema;

    shared_ptr<PGconn> m_connection;
};

#endif // CANVASREPOSITORY_H
