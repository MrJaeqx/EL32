#include "XboxControllerOfficial.h"
#include "XboxControllerStatus.h"
#include <cstddef>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <iostream>

using namespace std;

const uint16_t xboxControllerVendorId = 0x045e;
const uint16_t xboxControllerProductId = 0x028e;

const unsigned char endpointIN = 0x81;
const unsigned char endpointOUT = 0x01;

static uint16_t controllerIds = 0;

#define MAXRUMBLE { 0x00, 0x08, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00 };
#define NORUMBLE { 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
#define VARRUMBLE1 { 0x00, 0x08, 0x00,
#define VARRUMBLE2 , 0xff, 0x00, 0x00, 0x00 };

void * monitorController(void * arg);

XboxControllerOfficial::XboxControllerOfficial(libusb_device_handle * h, int serialNumber) :
        previous(NULL), current(NULL), generalCallback(NULL), monitoring(false), closed(false), serialNumber(serialNumber)
{
    handle = h;
}

vector<Controller *> XboxControllerOfficial::getAll(vector<Controller*> controllers)
{
    libusb_init (NULL);

    libusb_device **deviceList = NULL;
    ssize_t count = 0;

    count = libusb_get_device_list(NULL, &deviceList);
    for (ssize_t idx = 0; idx < count; idx++)
    {
        libusb_device *device = deviceList[idx];
        struct libusb_device_descriptor desc = { 0 };

        libusb_get_device_descriptor(device, &desc);

        if (desc.idVendor == xboxControllerVendorId && desc.idProduct == xboxControllerProductId)
        {
            uint8_t address = libusb_get_device_address(device);
            bool newDevice = true;

            for (int i = 0; i < controllers.size(); i++) {
                if (address == controllers[i]->getControllerId()) {
                    newDevice = false;
                }
            }
            if (newDevice) {
                printf("new device added\n");
                libusb_device_handle *h;
                libusb_open(device, &h);
                controllers.push_back(new XboxControllerOfficial(h, address));
            }
        }
    }

    libusb_free_device_list(deviceList, 1);

    return controllers;
}

void * monitorControllerOfficial(void * arg)
{
    XboxControllerOfficial * xboxController = (XboxControllerOfficial *) arg;
    xboxController->monitor();
    pthread_detach (pthread_self());return
NULL	;
}

void XboxControllerOfficial::startMonitoring()
{
    if (monitoring == false && closed == false) {
        printf("start monitoring\n");
        monitoring = true;
        pthread_t monitoringThread;
        pthread_create(&monitoringThread, NULL, monitorControllerOfficial, this);
    }
}

void XboxControllerOfficial::stopMonitoring()
{
    monitoring = false;
}

void XboxControllerOfficial::setGeneralCallback(
        void (*generalCallback)(Controller *, ControllerStatus *, ControllerStatus *))
{
    this->generalCallback = generalCallback;
}

void XboxControllerOfficial::rumbleMax()
{
    int transferred = 0;
    unsigned char rumbleMax[] = MAXRUMBLE;
    libusb_interrupt_transfer(handle, endpointOUT, rumbleMax, sizeof rumbleMax, &transferred, 0);
    if (transferred != sizeof rumbleMax)
    {
        perror("Error while sending.");
        close();
    }
}

void XboxControllerOfficial::rumbleVariable(unsigned char rumble)
{
    int transferred = 0;
    unsigned char rumbleVariable[] = VARRUMBLE1 rumble VARRUMBLE2
    libusb_interrupt_transfer(handle, endpointOUT, rumbleVariable, sizeof rumbleVariable, &transferred, 0);
    if (transferred != sizeof rumbleVariable)
    {
        perror("Error while sending.");
        close();
    }
}

void XboxControllerOfficial::rumbleOff()
{
    int transferred = 0;
    unsigned char noRumble[] = NORUMBLE;
    libusb_interrupt_transfer(handle, endpointOUT, noRumble, sizeof noRumble, &transferred, 0);
    if (transferred != sizeof noRumble)
    {
        perror("Error while sending.");
        close();
    }
}

void XboxControllerOfficial::close()
{
    closed = true;
    monitoring = false;
    libusb_close (handle);
}

void XboxControllerOfficial::setLeds(unsigned char mode)
{
    int transferred = 0;
    unsigned char ledMessage[] = { 0x01, 0x03, mode };
    libusb_interrupt_transfer(handle, endpointOUT, ledMessage, sizeof ledMessage, &transferred, 0);
    if (transferred != sizeof ledMessage)
    {
        perror("Error while sending.");
        close();
    }
}

bool XboxControllerOfficial::isClosed() {
    return closed && doneClosing;
}

uint8_t XboxControllerOfficial::getControllerId() {
    return serialNumber;
}

void XboxControllerOfficial::monitor()
{
    unsigned char inputReport[20];
    int transferred = 0;
    while (monitoring)
    {
        libusb_interrupt_transfer(handle, endpointIN, inputReport, sizeof inputReport, &transferred, 0);
        current = XboxControllerStatus::create(inputReport);
        if (current == NULL)
        {
            continue;
        }
        if (transferred != sizeof inputReport)
        {
            perror("Error while receiving.");
            if (current != NULL && previous != NULL) {
                close();
            }
            continue;
        }
        if (previous != NULL && generalCallback != NULL)
        {
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

    sleep(1);
    doneClosing = true;
}

