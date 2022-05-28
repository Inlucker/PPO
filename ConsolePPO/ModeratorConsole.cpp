#include "ModeratorConsole.h"

ModeratorConsole::ModeratorConsole(shared_ptr<CanvasRepository> canvas_rep, shared_ptr<UsersRepository> users_rep)
{
    moderator_controller = make_unique<ModeratorController>();
    users_repository = users_rep;
    canvas_repository = canvas_rep;
}

void ModeratorConsole::login(shared_ptr<UserBL> user_bl)
{
    cout << "\nLogged in moderator" << endl;
    moderator_controller->login(user_bl);
    users_repository->setRole(user_bl->getRole(), user_bl->getRole());

    input = -1;

    while (input != 0)
    {
        cout << endl;
        cout << "Commands:" << endl;
        cout << "1 - Show Free Users" << endl;
        cout << "2 - Show My Users" << endl;
        cout << "3 - Add user" << endl;
        cout << "4 - Delete user" << endl;
        cout << "5 - Delete this user" << endl;
        cout << "0 - Exit to BaseConsole\n" << endl;

        _flushall();
        cout << "Enter the number of command to be done: ";
        while (!(cin >> input))
        {
            cout << "Wrong input" << endl;
            cin.clear();
            _flushall();
            cout << "Enter the number of command to be done: ";
        }

        switch (input)
        {
            case 1:
            {
                vector<string> free_users_names = users_repository->getFreeCanvasUsers();
                cout << "Free users:" << endl;
                for (auto &elem : free_users_names)
                    cout << elem << endl;
                break;
            }
            case 2:
            {
                if (moderator_controller->getUser())
                {
                    vector<string> my_users_names = users_repository->getCanvasUsersByMid(moderator_controller->getUser()->getId());
                    cout << "My users:" << endl;
                    for (auto &elem : my_users_names)
                        cout << elem << endl;
                }
                break;
            }
            case 3:
            {
                _flushall();
                cout << "Enter user name to add: ";
                string name;
                getline(cin, name);

                shared_ptr<UserBL> user_bl = users_repository->getCanvasUser(name);
                UserBL new_user_bl(user_bl->getId(), user_bl->getLogin(), user_bl->getPassword(), user_bl->getRole(), moderator_controller->getUser()->getId());
                users_repository->updateUser(new_user_bl, user_bl->getId());
                break;
            }
            case 4:
            {
                _flushall();
                cout << "Enter user name to delete: ";
                string name;
                getline(cin, name);

                shared_ptr<UserBL> user_bl = users_repository->getCanvasUser(name);
                UserBL new_user_bl(user_bl->getId(), user_bl->getLogin(), user_bl->getPassword(), user_bl->getRole(), -1);
                users_repository->updateUser(new_user_bl, user_bl->getId());
                break;
            }
            case 5:
            {
                users_repository->deleteUser(moderator_controller->getUser()->getId());
                input = 0;
                cout << "Exiting..." << endl;
                break;
            }
            case 0:
            {
                cout << "Exiting..." << endl;
                break;
            }
            default:
            {
                cout << "Wrong command" << endl;
                break;
            }
        }
    }
}
