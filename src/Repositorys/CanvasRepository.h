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
    CanvasRepository(string dbhost, int dbport, string dbname, string dbuser, string dbpass, string dbschema);
    virtual ~CanvasRepository() = default;

    virtual shared_ptr<CanvasBL> getCanvas(int id);
    virtual void addCanvas(CanvasBL& canvas);
    virtual void deleteCanvas(int id) ;
    virtual void updateCanvas(CanvasBL& canvas_bl, int id);

protected:
    void connect();

//private:
    string m_dbhost = "localhost";
    int m_dbport = 5432;
    string m_dbname = "postgres";
    string m_dbuser = "postgres";
    string m_dbpass = "postgres";
    string m_dbschema = "PPO";

    shared_ptr<PGconn> m_connection;
};

#endif // CANVASREPOSITORY_H
