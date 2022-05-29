#ifndef PARAMSREPOSITORYMYSQL_H
#define PARAMSREPOSITORYMYSQL_H

#include "IParamsRepository.h"
#include "Errors/RepositoryErrors.h"

class ParamsRepositoryMySQL: public IParamsRepository
{
public:
    ParamsRepositoryMySQL();
    virtual ~ParamsRepositoryMySQL() = default;

    virtual shared_ptr<ParamsBL> getParams(int id) override;
    virtual void addParams(ParamsBL& params) override;
    virtual void deleteParams(int id) override;
    virtual void updateParams(ParamsBL& params, int id) override;

protected:
    string m_schema;
};

#endif // PARAMSREPOSITORYMYSQL_H
