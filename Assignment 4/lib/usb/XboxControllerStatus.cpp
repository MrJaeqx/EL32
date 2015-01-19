#include "XboxControllerStatus.h"
#include <stdio.h>

using namespace std;

// constructor
XboxControllerStatus::XboxControllerStatus(unsigned char inputReport[]) : ControllerStatus()
{
    for (int i = 0; i < 20; i++)
	{
		input[i] = inputReport[i];
	}
}

// creates a new instance of XboxControllerStatus
ControllerStatus * XboxControllerStatus::create(unsigned char input[])
{
    if ((input[0] & 1) != 0)
	{
		return NULL;
	}
    XboxControllerStatus * controllerStatus = new XboxControllerStatus(input);
	return controllerStatus;
}

// gets the status of all leftbuttons
char XboxControllerStatus::getLeft()
{
    //get 0x02 (offset: 2)
	int valueDPad = input[2] & 4;
	//get 0x03 (offset: 0)
	int valueLB = input[3] & 1;
	return valueDPad == 4 || valueLB == 1;

	// TODO:
	// IMPLEMENT OTHER STICKS AND BACKTRIGGERS
}

// gets the status of all rightbuttons
char XboxControllerStatus::getRight()
{
    //get 0x02 (offset: 3)
	int valueDPad = input[2] & 8;
	//get 0x03 (offset: 1)
	int valueRB = input[3] & 2;
	return valueDPad == 8 || valueRB == 2;

	// TODO:
	// IMPLEMENT OTHER STICKS AND BACKTRIGGERS
}

// gets the status of the startbutton
char XboxControllerStatus::getStartButton()
{
    //get 0x02 (offset: 4)
	int value = input[2] & 16;
	return value == 16;
}

// gets the status of the backbutton
char XboxControllerStatus::getBackButton()
{
    //get 0x02 (offset: 5)
	int value = input[2] & 32;
	return value == 32;
}

// get the value of the enterbutton
char XboxControllerStatus::getEnterButton()
{
    //get 0x03 (offset: 4)
	int value = input[3] & 16;
	return value == 16;
}
