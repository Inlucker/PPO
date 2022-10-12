#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "../Essensities/UserBL.h"

#include <memory>

using namespace std;

class BaseController
{
public:
    BaseController();
    explicit BaseController(shared_ptr<UserBL> u);
    virtual ~BaseController() = default;

    //virtual int login(int id, string l, string p, string r, int mod_id);
    virtual void login(shared_ptr<UserBL> u);
    virtual void logout() noexcept;
    //virtual int registrate(string l, string p, string r);
    virtual shared_ptr<UserBL> getUser() noexcept;

protected:
    shared_ptr<UserBL> user;
};

#endif // BASECONTROLLER_H
