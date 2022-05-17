#ifndef USERBL_H
#define USERBL_H

#include <string>

using namespace std;

class UserBL
{
public:
    UserBL();
    //UserBL& operator =(UserBL&& vec) noexcept;
    UserBL(int id, string l, string p, string r, int m_id);

    bool operator ==(UserBL& an_ubl);
    bool operator !=(UserBL& an_ubl);

    int getId();
    const string& getLogin() const;
    const string& getPassword() const;
    const string& getRole() const;
    int getModeratorId();

private:
    int id = NULL;
    string login = "";
    string password = "";
    string role = "";
    int moderator_id = NULL;

};

#endif // USERBL_H
