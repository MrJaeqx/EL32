#pragma once

#include "ControllerStatus.h"

using namespace std;

class XboxControllerStatus: public ControllerStatus
{

public:
    XboxControllerStatus(unsigned char i[]);
    static ControllerStatus * create(unsigned char input[]);
	virtual char getLeft();
    virtual char getRight();
    virtual char getStartButton();
    virtual char getBackButton();
    virtual char getEnterButton();
    static bool compare(ControllerStatus * previous, ControllerStatus * current);
private:
    unsigned char input[20];
};
