#ifndef XBOXCONTROLLER_H
#define XBOXCONTROLLER_H

#include <libusb-1.0/libusb.h>
#include <ControllerStatus.h>
#include <vector>

#define OFF 0x00
#define ALL_BLINKING 0x01
#define FLASH_1 0x02
#define FLASH_2 0x03
#define FLASH_3 0x04
#define FLASH_4 0x05
#define ON_1 0x06
#define ON_2 0x07
#define ON_3 0x08
#define ON_4 0x09
#define ROTATING 0x0a
#define BLINKING 0x0b
#define SLOW_BLINKING 0x0c
#define ALTERNATING 0x0d

class XboxController
{
public:
	static XboxController * getSingle();
	static std::vector<XboxController *> getAll();

	void startMonitoring();
	void stopMonitoring();

	void monitor();

	void rumbleMax();

	void rumbleVariable(unsigned char rumble);

	void rumbleOff();

	void setLeds(unsigned char mode);

	void close();

	void setGeneralCallback(void (*generalCallback)(XboxController *, ControllerStatus *, ControllerStatus *));
private:
	XboxController(libusb_device_handle * h);

	ControllerStatus * previous;
	ControllerStatus * current;

	libusb_device_handle * handle;

	void (*generalCallback)(XboxController *, ControllerStatus *, ControllerStatus *);

	volatile bool monitoring;
};

#endif
