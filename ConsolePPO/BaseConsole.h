#ifndef BASECONSOLE_H
#define BASECONSOLE_H

#include <memory>
#include <iostream>

using namespace std;

#include "CanvasUserConsole.h"
#include "ModeratorConsole.h"
#include "Controllers/BaseController.h"
#include "Repositorys/UsersRepository.h"

class BaseConsole
{
public:
    BaseConsole();

private:
    void loginCmd(string login, string password);
    void registrate(string login, string password, string role);

private:
    int input = -1;
    unique_ptr<CanvasUserConsole> canvas_user_console;
    unique_ptr<ModeratorConsole> moderator_console;
    shared_ptr<UsersRepository> user_repository;
};

#endif // BASECONSOLE_H
