#ifndef USERSREPOSITORYMYSQL_H
#define USERSREPOSITORYMYSQL_H

#include "IUsersRepository.h"
#include "Errors/RepositoryErrors.h"
#include <QSqlDatabase>

class UsersRepositoryMySQL : public IUsersRepository
{
public:
    UsersRepositoryMySQL();
    virtual ~UsersRepositoryMySQL() = default;

    virtual shared_ptr<UserBL> getUser(string login, string password) override;
    shared_ptr<UserBL> getCanvasUser(string name);
    vector<string> getFreeCanvasUsers();
    vector<string> getCanvasUsersByMid(int m_id);
    virtual void addUser(UserBL& user_bl) override;
    virtual void deleteUser(int id) override;
    virtual void updateUser(UserBL& user_bl, int id) override;

protected:
    string m_schema;

    //shared_ptr<QSqlDatabase> db;
};

#endif // USERSREPOSITORYMYSQL_H
