#ifndef CONTROLLERSTATUS_H
#define CONTROLLERSTATUS_H

#include <stdint.h>

class ControllerStatus
{
public:

	static ControllerStatus * create(unsigned char input[]);
	//1b
	char getDPadUp();
	char getDPadDown();
	char getDPadLeft();
	char getDPadRight();
	char getStartButton();
	char getBackButton();
	char getLeftStickPress();
	char getRightStickPress();
	char getButtonLB();
	char getButtonRB();
	char getButtonXboxButton();
	char getButtonA();
	char getButtonB();
	char getButtonX();
	char getButtonY();
	//8b
	unsigned char getLeftTrigger();
	unsigned char getRightTrigger();
	//16b
	int16_t getLeftStickXAxis();
	int16_t getLeftStickYAxis();
	int16_t getRightStickXAxis();
	int16_t getRightStickYAxis();

	//Returns true if there is a difference
	static bool compare(ControllerStatus * previous, ControllerStatus * current);
	
protected:
private:
	ControllerStatus(unsigned char i[]);
	unsigned char input[20];
};
#endif // CONTROLLERSTATUS_H
