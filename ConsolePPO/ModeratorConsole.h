#ifndef MODERATORCONSOLE_H
#define MODERATORCONSOLE_H

#include <iostream>
#include <memory>

using namespace std;

#include "Essensities/UserBL.h"

class ModeratorConsole
{
public:
    ModeratorConsole();

    void login(shared_ptr<UserBL> user_bl);
};

#endif // MODERATORCONSOLE_H
