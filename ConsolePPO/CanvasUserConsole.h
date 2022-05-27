#ifndef CANVASUSERCONSOLE_H
#define CANVASUSERCONSOLE_H

#include <iostream>
#include <memory>

using namespace std;

#include "Essensities/UserBL.h"

class CanvasUserConsole
{
public:
    CanvasUserConsole();

    void login(shared_ptr<UserBL> user_bl);
};

#endif // CANVASUSERCONSOLE_H
