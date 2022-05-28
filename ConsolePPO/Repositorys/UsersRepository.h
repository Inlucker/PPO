#ifndef USERSREPOSITORY_H
#define USERSREPOSITORY_H

#include <iostream>
#include <libpq-fe.h>

using namespace std;

#include "IUsersRepository.h"
#include "Errors/RepositoryErrors.h"

class UsersRepository : public IUsersRepository
{
public:
    UsersRepository();
    UsersRepository(string dbuser, string dbpass, string dbschema = "PPO", string dbhost = "localhost", int dbport = 5432, string dbname = "postgres");
    virtual ~UsersRepository() = default;

    virtual shared_ptr<UserBL> getUser(string login, string password) override;
    shared_ptr<UserBL> getCanvasUser(string name);
    vector<string> getFreeCanvasUsers();
    vector<string> getCanvasUsersByMid(int m_id);
    virtual void addUser(UserBL& user) override;
    virtual void deleteUser(int id) override;
    virtual void updateUser(UserBL& user_bl, int id) override;

    void setRole(string login, string password);

protected:
    void connect();

    string m_dbhost ;
    int m_dbport;
    string m_dbname;
    string m_dbuser;
    string m_dbpass;
    string m_dbschema;

    shared_ptr<PGconn> m_connection;
};

#endif // USERSREPOSITORY_H
