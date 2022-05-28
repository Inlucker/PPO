#ifndef CANVASUSERCONSOLE_H
#define CANVASUSERCONSOLE_H

#include <iostream>
#include <memory>

using namespace std;

#include "Essensities/UserBL.h"
#include "Controllers/usercontroller.h"
#include "Repositorys/CanvasRepository.h"
#include "Repositorys/UsersRepository.h"

class CanvasUserConsole
{
public:
    CanvasUserConsole(shared_ptr<CanvasRepository> canvas_rep, shared_ptr<UsersRepository> users_rep);

    void login(shared_ptr<UserBL> user_bl);

private:
    int input = -1;
    unique_ptr<UserController> user_controller;
    shared_ptr<CanvasRepository> canvas_repository;
    shared_ptr<UsersRepository> users_repository;
};

#endif // CANVASUSERCONSOLE_H
