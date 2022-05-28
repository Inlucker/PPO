#ifndef MODERATORCONSOLE_H
#define MODERATORCONSOLE_H

#include <iostream>
#include <memory>

using namespace std;

#include "Essensities/UserBL.h"
#include "Controllers/ModeratorController.h"
#include "Repositorys/CanvasRepository.h"
#include "Repositorys/UsersRepository.h"

class ModeratorConsole
{
public:
    ModeratorConsole(shared_ptr<CanvasRepository> canvas_rep, shared_ptr<UsersRepository> users_rep);

    void login(shared_ptr<UserBL> user_bl);

private:
    int input = -1;
    unique_ptr<ModeratorController> moderator_controller;
    shared_ptr<CanvasRepository> canvas_repository;
    shared_ptr<UsersRepository> users_repository;
};

#endif // MODERATORCONSOLE_H
