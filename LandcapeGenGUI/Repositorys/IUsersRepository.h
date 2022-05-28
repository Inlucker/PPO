#ifndef IUSERSREPOSITORY_H
#define IUSERSREPOSITORY_H

#include <memory>
#include <vector>

using namespace std;

#include "Essensities/UserBL.h"

class IUsersRepository
{
public:
    IUsersRepository();
    virtual ~IUsersRepository() = 0;

    virtual shared_ptr<UserBL> getUser(string login, string password) = 0;
    /*virtual shared_ptr<UserBL> getCanvasUser(string name) = 0;
    virtual vector<string>  getFreeCanvasUsers() = 0;
    virtual vector<string> getCanvasUsersByMid(int m_id) = 0;*/
    virtual void addUser(UserBL& user_bl) = 0;
    virtual void deleteUser(int id) = 0;
    virtual void updateUser(UserBL& user_bl, int id) = 0;
};

#endif // IUSERSREPOSITORY_H
