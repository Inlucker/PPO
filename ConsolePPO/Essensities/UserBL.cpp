#include "UserBL.h"

UserBL::UserBL()
{
    id = NULL;
    login = "";
    password = "";
    role = "";
    moderator_id = NULL;
}

UserBL::UserBL(int i, string l, string p, string r, int m_id)
{
    id = i;
    login = l;
    password = p;
    role = r;
    moderator_id = m_id;
}

bool UserBL::operator ==(UserBL &an_ubl)
{
    bool res = true;

    if (this->id != an_ubl.id ||
            this->login != an_ubl.login ||
            this->password != an_ubl.password ||
            this->role != an_ubl.role ||
            this->moderator_id != an_ubl.moderator_id)
        res = false;
    return res;
}

bool UserBL::operator !=(UserBL &an_ubl)
{
    return !(*this == an_ubl);
}

/*UserBL &UserBL::operator =(UserBL &&u) noexcept
{
    login = u.getLogin();
    password = u.getPassword();
    role = u.getRole();
    moderator_id = u.getModeratorId();

    return *this;
}*/

int UserBL::getId()
{
    return id;
}

const string& UserBL::getLogin() const
{
    return login;
}

const string& UserBL::getPassword() const
{
    return password;
}

const string& UserBL::getRole() const
{
    return role;
}

int UserBL::getModeratorId()
{
    return moderator_id;
}
