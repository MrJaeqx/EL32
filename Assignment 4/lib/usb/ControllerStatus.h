#ifndef __ControllerStatus_h__
#define __ControllerStatus_h__

#include "Controller.h"

using namespace std;

class ControllerStatus
{
public:
    virtual char getLeft() = 0;
    virtual char getRight() = 0;
    virtual char getStartButton() = 0;
    virtual char getBackButton() = 0;
    virtual char getEnterButton() = 0;
    static bool compare(ControllerStatus * previous, ControllerStatus * current);
};

#endif
