#include "Controller.h"
#include "XboxController.h"
#include "XboxControllerOfficial.h"
#include <vector>
using std::vector;

vector<Controller *> Controller::getAll(vector<Controller*> controllers) {
    vector<Controller *> xboxControllers = XboxController::getAll(controllers);
    //vector<Controller *> xboxControllersOfficial = XboxControllerOfficial::getAll(controllers);


    //xboxControllers.insert(xboxControllers.end(), xboxControllersOfficial.begin(), xboxControllersOfficial.end());


    return xboxControllers;
}
