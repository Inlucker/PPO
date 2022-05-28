#include "CanvasUserConsole.h"

CanvasUserConsole::CanvasUserConsole(shared_ptr<CanvasRepository> canvas_rep, shared_ptr<UsersRepository> users_rep)
{
    user_controller = make_unique<UserController>();
    users_repository = users_rep;
    canvas_repository = canvas_rep;
}

void CanvasUserConsole::login(shared_ptr<UserBL> user_bl)
{
    cout << "\nLogged in canvas user" << endl;
    user_controller->login(user_bl);
    canvas_repository->setRole(user_bl->getRole(), user_bl->getRole());
    users_repository->setRole(user_bl->getRole(), user_bl->getRole());

    input = -1;

    while (input != 0)
    {
        cout << endl;
        cout << "Commands:" << endl;
        cout << "1 - Generate Landscape" << endl;
        cout << "2 - Clean" << endl;
        cout << "3 - Move" << endl;
        cout << "4 - Scale" << endl;
        cout << "5 - Rotate" << endl;
        cout << "6 - Send Canvas" << endl;
        cout << "7 - Load Canvas" << endl;
        cout << "8 - Update Canvas" << endl;
        cout << "9 - Delete Canvas" << endl;
        cout << "10 - Delete this user" << endl;
        cout << "11 - Print HeightsMapPoints" << endl;
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
                user_controller->generateNewLandscape(5);
                //cout << "Generated HeightsMap:\n" << *user_controller->getHeightsMap() << endl;
                cout << "Generated HeightsMapPoints:\n" << *user_controller->getHeightsMapPoints() << endl;
                break;
            }
            case 2:
            {
                user_controller->cleanCanvas();
                user_controller->resetHeightsMap();
                //cout << "Canvas cleaned:\n" << *user_controller->getHeightsMap() << endl;
                cout << "Canvas cleaned:\n" << *user_controller->getHeightsMapPoints() << endl;
                break;
            }
            case 3:
            {
                user_controller->move(Point(100, 100, 100));
                cout << "Landscape moved:\n" << *user_controller->getHeightsMapPoints() << endl;
                break;
            }
            case 4:
            {
                user_controller->scale(Point(2, 2, 2));
                cout << "Landscape scaled:\n" << *user_controller->getHeightsMapPoints() << endl;
                break;
            }
            case 5:
            {
                user_controller->rotate(Point(90, 60, 30));
                cout << "Landscape rotated:\n" << *user_controller->getHeightsMapPoints() << endl;
                break;
            }
            case 6:
            {
                _flushall();
                cout << "Enter canvas name: ";
                string name;
                getline(cin, name);

                int r, g, b, u_id;
                user_controller->getColor(r, g, b);
                u_id = user_controller->getUser()->getId();

                CanvasBL cbl = CanvasBL(u_id, name, *(user_controller->getHeightsMap()), *user_controller->getHeightsMapPoints(), r, g, b);
                canvas_repository->addCanvas(cbl);
                break;
            }
            case 7:
            {
                _flushall();
                cout << "Enter canvas id to load: ";
                string tmp;
                getline(cin, tmp);
                int id = stoi(tmp);

                shared_ptr<CanvasBL> canvas_bl = canvas_repository->getCanvas(id);
                int r, g, b;
                canvas_bl->getColor(r, g, b);

                //user_controller->selectCanvas(c);
                user_controller->selectCanvas(make_shared<LandscapeCanvas>(canvas_bl->getHeightsMap(), canvas_bl->getHeightsMapPoints(), r, g, b));

                user_controller->getHeightsMapPoints() = user_controller->getHeightsMapPoints();
                user_controller->getTriPolArray() =  user_controller->getTriPolArray();

                cout << "Loaded HeightsMapPoints:\n" << *user_controller->getHeightsMapPoints() << endl;

                break;
            }
            case 8:
            {
                _flushall();
                cout << "Enter canvas id to update: ";
                string tmp;
                getline(cin, tmp);
                int id = stoi(tmp);

                int r, g, b, u_id;
                user_controller->getColor(r, g, b);
                u_id = user_controller->getUser()->getId();
                string name = "CanvasName";
                CanvasBL canvas_bl = CanvasBL(u_id, name, *(user_controller->getHeightsMap()), *user_controller->getHeightsMapPoints(), r, g, b);
                canvas_repository->updateCanvas(canvas_bl, id);

                break;
            }
            case 9:
            {
                _flushall();
                cout << "Enter canvas id to delete: ";
                string tmp;
                getline(cin, tmp);
                int id = stoi(tmp);

                canvas_repository->deleteCanvas(id);

                break;
            }
            case 10:
            {
                users_repository->deleteUser(user_controller->getUser()->getId());
                input = 0;
                cout << "Exiting..." << endl;
                break;
            }
            case 11:
            {
                cout << "Print HeightsMapPoints:\n" << *user_controller->getHeightsMapPoints() << endl;
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
