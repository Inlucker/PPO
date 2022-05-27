#include "UserControllerTest.h"

UserControllerTest::UserControllerTest()
{
    cout << selectCanvasTest() << endl;
}

bool UserControllerTest::selectCanvasTest()
{
    shared_ptr<UserController> controller = make_shared<UserController>();
    int size = 33;
    HeightsMap heights_map = HeightsMap(size);
    heights_map.diamondSquare();
    shared_ptr<LandscapeCanvas> canvas = make_shared<LandscapeCanvas>(heights_map);
    controller->selectCanvas(canvas);

    return (canvas.get() == controller->getLandscapeCanvas().get());
}
