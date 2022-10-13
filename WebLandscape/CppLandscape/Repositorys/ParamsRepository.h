#ifndef PARAMSREPOSITORY_H
#define PARAMSREPOSITORY_H

#include "../Repositorys/IParamsRepository.h"

#include <string>
#include <libpq-fe.h>

class ParamsRepository : public IParamsRepository
{
public:
    //ParamsRepository();
    ParamsRepository(string dbuser = "guest", string dbpass = "guest", string dbschema = "PPO", string dbhost = "localhost", int dbport = 5432, string dbname = "postgres");
    virtual ~ParamsRepository() = default;

    virtual shared_ptr<ParamsBL> getParams(int id) override;
    virtual void addParams(ParamsBL& params) override;
    virtual void deleteParams(int id) override;
    virtual void updateParams(ParamsBL& params, int id) override;


protected:
    void connect();

    string m_dbhost;
    int m_dbport;
    string m_dbname;
    string m_dbuser;
    string m_dbpass;
    string m_schema;

    shared_ptr<PGconn> m_connection;
};

#endif // PARAMSREPOSITORY_H
