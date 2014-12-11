#include <XboxController.h>
#include <cstddef>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>
using std::vector;

const uint16_t xboxControllerVendorId = 0x045e;
const uint16_t xboxControllerProductId = 0x028e;

const unsigned char endpointIN = 0x81;
const unsigned char endpointOUT = 0x02;

#define MAXRUMBLE { 0x00, 0x08, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00 };
#define NORUMBLE { 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
#define VARRUMBLE1 { 0x00, 0x08, 0x00, 
#define VARRUMBLE2 , 0xff, 0x00, 0x00, 0x00 };

void * monitorController(void * arg);

XboxController::XboxController(libusb_device_handle * h) :
		previous(NULL), current(NULL), generalCallback(NULL), monitoring(false)
{
	handle = h;
}

XboxController * XboxController::getSingle()
{
	libusb_init (NULL);

	libusb_device **deviceList = NULL;
	ssize_t count = 0;

	count = libusb_get_device_list(NULL, &deviceList);

	XboxController * xboxController = NULL;

	for (ssize_t idx = 0; idx < count; idx++)
	{
		libusb_device *device = deviceList[idx];
		struct libusb_device_descriptor desc = { 0 };

		libusb_get_device_descriptor(device, &desc);

		if (xboxController == NULL && desc.idVendor == xboxControllerVendorId
				&& desc.idProduct == xboxControllerProductId)
		{
			libusb_device_handle *h;
			libusb_open(device, &h);
			xboxController = new XboxController(h);
		}
	}

	libusb_free_device_list(deviceList, 1);

	return xboxController;
}

vector<XboxController *> XboxController::getAll()
{
	libusb_init (NULL);

	libusb_device **deviceList = NULL;
	ssize_t count = 0;
	vector<XboxController *> results;

	count = libusb_get_device_list(NULL, &deviceList);

	for (ssize_t idx = 0; idx < count; idx++)
	{
		libusb_device *device = deviceList[idx];
		struct libusb_device_descriptor desc = { 0 };

		libusb_get_device_descriptor(device, &desc);

		if (desc.idVendor == xboxControllerVendorId && desc.idProduct == xboxControllerProductId)
		{
			libusb_device_handle *h;
			libusb_open(device, &h);
			results.push_back(new XboxController(h));
		}
	}

	libusb_free_device_list(deviceList, 1);

	return results;
}

void * monitorController(void * arg)
{
	XboxController * xboxController = (XboxController *) arg;
	xboxController->monitor();
	pthread_detach (pthread_self());return
NULL	;
}

void XboxController::startMonitoring()
{
	monitoring = true;
	pthread_t monitoringThread;
	pthread_create(&monitoringThread, NULL, monitorController, this);
}

void XboxController::stopMonitoring()
{
	monitoring = false;
}

void XboxController::setGeneralCallback(
		void (*generalCallback)(XboxController *, ControllerStatus *, ControllerStatus *))
{
	this->generalCallback = generalCallback;
}

void XboxController::rumbleMax()
{
	int transferred = 0;
	unsigned char rumbleMax[] = MAXRUMBLE;
	libusb_interrupt_transfer(handle, endpointOUT, rumbleMax, sizeof rumbleMax, &transferred, 0);
	if (transferred != sizeof rumbleMax)
	{
		perror("Error while sending.");
	}
}

void XboxController::rumbleVariable(unsigned char rumble)
{
	int transferred = 0;
	unsigned char rumbleVariable[] = VARRUMBLE1 rumble VARRUMBLE2
	libusb_interrupt_transfer(handle, endpointOUT, rumbleVariable, sizeof rumbleVariable, &transferred, 0);
	if (transferred != sizeof rumbleVariable)
	{
		perror("Error while sending.");
	}
}

void XboxController::rumbleOff()
{
	int transferred = 0;
	unsigned char noRumble[] = NORUMBLE;
	libusb_interrupt_transfer(handle, endpointOUT, noRumble, sizeof noRumble, &transferred, 0);
	if (transferred != sizeof noRumble)
	{
		perror("Error while sending.");
	}
}

void XboxController::close()
{
	libusb_close (handle);
}

void XboxController::setLeds(unsigned char mode)
{
	int transferred = 0;
	unsigned char ledMessage[] = { 0x01, 0x03, mode };
	libusb_interrupt_transfer(handle, endpointOUT, ledMessage, sizeof ledMessage, &transferred, 0);
	if (transferred != sizeof ledMessage)
	{
		perror("Error while sending.");
	}
}

void XboxController::monitor()
{
	unsigned char inputReport[20];
	int transferred = 0;
	while (monitoring)
	{
		libusb_interrupt_transfer(handle, endpointIN, inputReport, sizeof inputReport, &transferred, 0);
		current = ControllerStatus::create(inputReport);
		if (current == NULL)
		{
			continue;
		}
		if (transferred != sizeof inputReport)
		{
			perror("Error while receiving.");
			continue;
		}
		if (previous != NULL && generalCallback != NULL)
		{
			ControllerStatus::compareDebug(previous, current);
			if (ControllerStatus::compare(previous, current))
			{
				generalCallback(this, previous, current);
			}
		}
		if (previous != NULL)
		{
			delete previous;
		}

		previous = current;
		usleep(10000); // sleep for 10 ms 
	}
	if (previous != NULL)
	{
		delete previous;
		previous = NULL;
	}
	current = NULL;
}

