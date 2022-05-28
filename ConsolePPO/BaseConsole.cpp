#include "BaseConsole.h"

BaseConsole::BaseConsole()
{
    user_repository = make_shared<UsersRepository>();
    canvas_repository = make_shared<CanvasRepository>();
    canvas_user_console = make_unique<CanvasUserConsole>(canvas_repository, user_repository);
    moderator_console = make_unique<ModeratorConsole>(canvas_repository, user_repository);

    while (input != 0)
    {
        canvas_repository->setRole("guest", "guest");
        user_repository->setRole("guest", "guest");
        cout << endl;
        cout << "Commands:" << endl;
        cout << "1 - Login" << endl;
        cout << "2 - Registrate" << endl;
        cout << "0 - Exit from programm\n" << endl;

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
                _flushall();
                cout << "Enter login: ";
                string login;
                getline(cin, login);

                cout << "Enter password: ";
                string password;
                getline(cin, password);

                loginCmd(login, password);
                break;
            }
            case 2:
            {
                _flushall();
                cout << "Enter login: ";
                string login;
                getline(cin, login);

                cout << "Enter password: ";
                string password;
                getline(cin, password);

                cout << "Choose role (1 - canvas_user, 2 - moderator): ";
                string role_str, role = "";
                getline(cin, role_str);
                int tmp = stoi(role_str);
                if (tmp == 1)
                    role = "canvas_user";
                else if (tmp == 2)
                    role = "moderator";
                else
                {
                    cout << "No such role" << endl;
                    break;
                }

                registrate(login, password, role);
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

void BaseConsole::loginCmd(string login, string password)
{
    try
    {
        shared_ptr<UserBL> user_bl = user_repository->getUser(login, password);
        if (user_bl->getRole() == "canvas_user")
        {
            canvas_user_console->login(user_bl);
        }
        else if (user_bl->getRole() == "moderator")
        {
            moderator_console->login(user_bl);
        }
        else
        {
            cout << "No such role" << endl;
        }
    }
    catch (BaseError &er)
    {
        cout << er.what() << endl;
    }
    catch (...)
    {
        cout << "Unexpected Error" << endl;
    }
}

void BaseConsole::registrate(string login, string password, string role)
{
    try
    {
        UserBL user_bl(0, login, password, role, 0);
        user_repository->addUser(user_bl);
        cout << "Registration completed" << endl;
    }
    catch (BaseError &er)
    {
        cout << er.what() << endl;
    }
    catch (...)
    {
        cout << "Unexpected Error" << endl;
    }
}
