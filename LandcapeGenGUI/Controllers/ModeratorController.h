#ifndef MODERATORCONTROLLER_H
#define MODERATORCONTROLLER_H

#include "Controllers/BaseController.h"

#include <memory>

using namespace std;

class ModeratorController : public BaseController
{
public:
    ModeratorController();

    // void login(shared_ptr<UserBL> u) override;

    //void addUser(int id);
    //void deleteUser(int id);

private:
    //shared_ptr<IUsersRepository> user_repository;
};

#endif // MODERATORCONTROLLER_H
