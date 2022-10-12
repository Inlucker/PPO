#ifndef IPARAMSREPOSITORY_H
#define IPARAMSREPOSITORY_H

#include "../Essensities/ParamsBL.h"
#include <memory>

using namespace std;

class IParamsRepository
{
public:
    IParamsRepository();
    virtual ~IParamsRepository() = 0;

    virtual shared_ptr<ParamsBL> getParams(int id) = 0;
    virtual void addParams(ParamsBL& params) = 0;
    virtual void deleteParams(int id) = 0;
    virtual void updateParams(ParamsBL& params, int id) = 0;
};

#endif // IPARAMSREPOSITORY_H
