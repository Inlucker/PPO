#include "BaseController.h"

BaseController::BaseController()
{
    user = make_shared<UserBL>();
}

BaseController::BaseController(shared_ptr<UserBL> u)
{
    user = u;
}

/*int BaseController::login(int id, string l, string p, string r, int mod_id)
{
    user = make_shared<UserBL>(id, l, p, r, mod_id);
    //user.reset(new UserBL(l, p, r, NULL));
    return 0;
}*/

void BaseController::login(shared_ptr<UserBL> u)
{
    user = u;
}

void BaseController::logout() noexcept
{
    user.reset();
}

shared_ptr<UserBL> BaseController::getUser() noexcept
{
    return user;
}

/*int BaseController::registrate(string l, string p, string r)
{
    user = make_shared<UserBL>(l, p, r, NULL);
    return 0;
}*/
