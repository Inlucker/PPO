#include "CanvasUserConsole.h"

CanvasUserConsole::CanvasUserConsole()
{
    user_controller = make_unique<UserController>();
    //canvas_repository = shared_ptr<ICanvasRepository>(new CanvasRepository());
    users_repository.reset();
    canvas_repository.reset();
}

void CanvasUserConsole::login(shared_ptr<UserBL> user_bl)
{
    cout << "loged in canvas user" << endl;
    user_controller->login(user_bl);
    canvas_repository = make_shared<CanvasRepository>(user_bl->getRole(), user_bl->getRole());
    users_repository = make_shared<UsersRepository>("moderator", "moderator");


}
