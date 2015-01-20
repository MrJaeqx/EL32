#include "ControllerStatus.h"
#include <cstddef>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

ControllerStatus::ControllerStatus(unsigned char inputReport[])
{
	for (int i = 0; i < 20; i++)
	{
		input[i] = inputReport[i];
	}
}

ControllerStatus * ControllerStatus::create(unsigned char input[])
{
	if ((input[0] & 1) != 0)
	{
		return NULL;
	}
	ControllerStatus * controllerStatus = new ControllerStatus(input);
	return controllerStatus;
}

char ControllerStatus::getDPadUp()
{
	//get 0x02 (offset: 0)
	int value = input[2] & 1;
	return value == 1;
}

char ControllerStatus::getDPadDown()
{
	//get 0x02 (offset: 1)
	int value = input[2] & 2;
	return value == 2;
}

char ControllerStatus::getDPadLeft()
{
	//get 0x02 (offset: 2)
	int value = input[2] & 4;
	return value == 4;
}

char ControllerStatus::getDPadRight()
{
	//get 0x02 (offset: 3)
	int value = input[2] & 8;
	return value == 8;
}

char ControllerStatus::getStartButton()
{
	//get 0x02 (offset: 4)
	int value = input[2] & 16;
	return value == 16;
}

char ControllerStatus::getBackButton()
{
	//get 0x02 (offset: 5)
	int value = input[2] & 32;
	return value == 32;
}

char ControllerStatus::getLeftStickPress()
{
	//get 0x02 (offset: 6)
	int value = input[2] & 64;
	return value == 64;
}

char ControllerStatus::getRightStickPress()
{
	//get 0x02 (offset: 7)
	int value = input[2] & 128;
	return value == 128;
}

char ControllerStatus::getButtonLB()
{
	//get 0x03 (offset: 0)
	int value = input[3] & 1;
	return value == 1;
}

char ControllerStatus::getButtonRB()
{
	//get 0x03 (offset: 1)
	int value = input[3] & 2;
	return value == 2;
}

char ControllerStatus::getButtonXboxButton()
{
	//get 0x03 (offset: 2)
	int value = input[3] & 4;
	return value == 4;
}

char ControllerStatus::getButtonA()
{
	//get 0x03 (offset: 4)
	int value = input[3] & 16;
	return value == 16;
}

char ControllerStatus::getButtonB()
{
	//get 0x03 (offset: 5)
	int value = input[3] & 32;
	return value == 32;
}

char ControllerStatus::getButtonX()
{
	//get 0x03 (offset: 6)
	int value = input[3] & 64;
	return value == 64;
}

char ControllerStatus::getButtonY()
{
	//get 0x03 (offset: 7)
	int value = input[3] & 128;
	return value == 128;
}

//8b
unsigned char ControllerStatus::getLeftTrigger()
{
	//get 0x04 (offset: 0)
	return input[4];
}

unsigned char ControllerStatus::getRightTrigger()
{
	//get 0x05 (offset: 0)
	return input[5];
}

//16b
int16_t ControllerStatus::getLeftStickXAxis()
{
	//get 0x06 (offset: 0)
	//and 0x07 (offset: 0)
	return ((input[7] << 8) + input[6]);
}

int16_t ControllerStatus::getLeftStickYAxis()
{
	//get 0x08 (offset: 0)
	//and 0x09 (offset: 0)
	return ((input[9] << 8) + input[8]);
}

int16_t ControllerStatus::getRightStickXAxis()
{
	//get 0x0a (offset: 0)
	//and 0x0b (offset: 0)
	return ((input[0x0b] << 8) + input[0x0a]);
}

int16_t ControllerStatus::getRightStickYAxis()
{
	//get 0x0c (offset: 0)
	//and 0x0d (offset: 0)
	return ((input[0x0d] << 8) + input[0x0c]);
}

bool ControllerStatus::compare(ControllerStatus * previous, ControllerStatus * current)
{
	bool difference = false;

	if (previous->getLeftTrigger() != current->getLeftTrigger())
	{
		difference = true;
	}
	else if (previous->getRightTrigger() != current->getRightTrigger())
	{
		difference = true;
	}
	else if (abs(previous->getLeftStickXAxis() - current->getLeftStickXAxis()) > 100)
	{
		difference = true;
	}
	else if (abs(previous->getLeftStickYAxis() - current->getLeftStickYAxis()) > 100)
	{
		difference = true;
	}
	else if (abs(previous->getRightStickXAxis() - current->getRightStickXAxis()) > 100)
	{
		difference = true;
	}
	else if (abs(previous->getRightStickYAxis() - current->getRightStickYAxis()) > 100)
	{
		difference = true;
	}
	else if (previous->getDPadUp() != current->getDPadUp())
	{
		difference = true;
	}
	else if (previous->getDPadDown() != current->getDPadDown())
	{
		difference = true;
	}
	else if (previous->getDPadLeft() != current->getDPadLeft())
	{
		difference = true;
	}
	else if (previous->getDPadRight() != current->getDPadRight())
	{
		difference = true;
	}
	else if (previous->getStartButton() != current->getStartButton())
	{
		difference = true;
	}
	else if (previous->getBackButton() != current->getBackButton())
	{
		difference = true;
	}
	else if (previous->getLeftStickPress() != current->getLeftStickPress())
	{
		difference = true;
	}
	else if (previous->getRightStickPress() != current->getRightStickPress())
	{
		difference = true;
	}
	else if (previous->getButtonLB() != current->getButtonLB())
	{
		difference = true;
	}
	else if (previous->getButtonRB() != current->getButtonRB())
	{
		difference = true;
	}
	else if (previous->getButtonXboxButton() != current->getButtonXboxButton())
	{
		difference = true;
	}
	else if (previous->getButtonA() != current->getButtonA())
	{
		difference = true;
	}
	else if (previous->getButtonB() != current->getButtonB())
	{
		difference = true;
	}
	else if (previous->getButtonX() != current->getButtonX())
	{
		difference = true;
	}
	else if (previous->getButtonY() != current->getButtonY())
	{
		difference = true;
	}
	return difference;
}

// void ControllerStatus::compareDebug(ControllerStatus * previous, ControllerStatus * current)
// {

// 	if (previous->getLeftTrigger() != current->getLeftTrigger())
// 	{
// 		printf("getLeftTrigger is now: %i\n", current->getLeftTrigger());
// 	}
// 	if (previous->getRightTrigger() != current->getRightTrigger())
// 	{
// 		printf("getRightTrigger is now: %i\n", current->getRightTrigger());
// 	}
// 	if (abs(previous->getLeftStickXAxis() - current->getLeftStickXAxis()) > 100)
// 	{
// 		printf("getLeftStickXAxis is now: %i\n", current->getLeftStickXAxis());
// 	}
// 	if (abs(previous->getLeftStickYAxis() - current->getLeftStickYAxis()) > 100)
// 	{
// 		printf("getLeftStickYAxis is now: %i\n", current->getLeftStickYAxis());
// 	}
// 	if (abs(previous->getRightStickXAxis() - current->getRightStickXAxis()) > 100)
// 	{
// 		printf("getRightStickXAxis is now: %i\n", current->getRightStickXAxis());
// 	}
// 	if (abs(previous->getRightStickYAxis() - current->getRightStickYAxis()) > 100)
// 	{
// 		printf("getRightStickYAxis is now: %i\n", current->getRightStickYAxis());
// 	}

// 	if (previous->getDPadUp() != current->getDPadUp())
// 	{
// 		printf("getDPadUp is now: %s\n", current->getDPadUp() ? "pressed" : "released");
// 	}
// 	if (previous->getDPadDown() != current->getDPadDown())
// 	{
// 		printf("getDPadDown is now: %s\n", current->getDPadDown() ? "pressed" : "released");
// 	}
// 	if (previous->getDPadLeft() != current->getDPadLeft())
// 	{
// 		printf("getDPadLeft is now: %s\n", current->getDPadLeft() ? "pressed" : "released");
// 	}
// 	if (previous->getDPadRight() != current->getDPadRight())
// 	{
// 		printf("getDPadRight is now: %s\n", current->getDPadRight() ? "pressed" : "released");
// 	}
// 	if (previous->getStartButton() != current->getStartButton())
// 	{
// 		printf("getStartButton is now: %s\n", current->getStartButton() ? "pressed" : "released");
// 	}
// 	if (previous->getBackButton() != current->getBackButton())
// 	{
// 		printf("getBackButton is now: %s\n", current->getBackButton() ? "pressed" : "released");
// 	}
// 	if (previous->getLeftStickPress() != current->getLeftStickPress())
// 	{
// 		printf("getLeftStickPress is now: %s\n", current->getLeftStickPress() ? "pressed" : "released");
// 	}
// 	if (previous->getRightStickPress() != current->getRightStickPress())
// 	{
// 		printf("getRightStickPress is now: %s\n", current->getRightStickPress() ? "pressed" : "released");
// 	}
// 	if (previous->getButtonLB() != current->getButtonLB())
// 	{
// 		printf("getButtonLB is now: %s\n", current->getButtonLB() ? "pressed" : "released");
// 	}
// 	if (previous->getButtonRB() != current->getButtonRB())
// 	{
// 		printf("getButtonRB is now: %s\n", current->getButtonRB() ? "pressed" : "released");
// 	}
// 	if (previous->getButtonXboxButton() != current->getButtonXboxButton())
// 	{
// 		printf("getButtonXboxButton is now: %s\n", current->getButtonXboxButton() ? "pressed" : "released");
// 	}
// 	if (previous->getButtonA() != current->getButtonA())
// 	{
// 		printf("getButtonA is now: %s\n", current->getButtonA() ? "pressed" : "released");
// 	}
// 	if (previous->getButtonB() != current->getButtonB())
// 	{
// 		printf("getButtonB is now: %s\n", current->getButtonB() ? "pressed" : "released");
// 	}
// 	if (previous->getButtonX() != current->getButtonX())
// 	{
// 		printf("getButtonX is now: %s\n", current->getButtonX() ? "pressed" : "released");
// 	}
// 	if (previous->getButtonY() != current->getButtonY())
// 	{
// 		printf("getButtonY is now: %s\n", current->getButtonY() ? "pressed" : "released");
// 	}
// }

