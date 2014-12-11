#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ControllerStatus.h>
#include <XboxController.h>
#include <libusb-1.0/libusb.h>
#include <vector>
using std::vector;

static void generalCallback(XboxController * caller, ControllerStatus * previous, ControllerStatus * current);

int main(void)
{

	//Get a list of xboxControllers and monitor them all.
	vector<XboxController *> controllers = XboxController::getAll();
	for (unsigned int i = 0; i < controllers.size(); i++)
	{
		controllers[i]->setGeneralCallback(generalCallback);
		controllers[i]->startMonitoring();
	}

	while (true)
	{
		//Just wait and monitor the xboxController's
	}

	//For showing how to close usb:
	for (unsigned int i = 0; i < controllers.size(); i++)
	{
		controllers[i]->close();
	}

	libusb_exit (NULL);

	return 0;
}

//Demo code
static void generalCallback(XboxController * caller, ControllerStatus * previous, ControllerStatus * current)
{
	// Set rumble on when a is pressed and set it off when it is released

	if (!previous->getButtonA() && current->getButtonA())
	{
		caller->rumbleMax();
	}
	else if (previous->getButtonA() && !current->getButtonA())
	{
		caller->rumbleOff();
	}

	// Set led mode to rotating when x is pressed
	if (!previous->getButtonX() && current->getButtonX())
	{
		caller->setLeds(ROTATING);
	}

	// Set led mode to alternating when Y is pressed
	if (!previous->getButtonY() && current->getButtonY())
	{
		caller->setLeds(ALTERNATING);
	}

	// Set led mode to Blinking when B is pressed
	if (!previous->getButtonB() && current->getButtonB())
	{
		caller->setLeds(BLINKING);
	}

	// Set led 1 on when dpadup is pressed
	if (!previous->getDPadUp() && current->getDPadUp())
	{
		caller->setLeds(ON_1);
	}
	// Set led 2 on when dpadright is pressed
	if (!previous->getDPadRight() && current->getDPadRight())
	{
		caller->setLeds(ON_2);
	}
	// Set led 3 on when dpadleft is pressed
	if (!previous->getDPadLeft() && current->getDPadLeft())
	{
		caller->setLeds(ON_3);
	}
	// Set led 4 on when dpaddown is pressed
	if (!previous->getDPadDown() && current->getDPadDown())
	{
		caller->setLeds(ON_4);
	}
}
