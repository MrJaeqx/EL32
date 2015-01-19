#ifndef __XboxControllerOfficial_h__
#define __XboxControllerOfficial_h__

#include <vector>
#include <libusb-1.0/libusb.h>
#include "ControllerStatus.h"
#include "Controller.h"
#include <stdint.h>


using namespace std;
class XboxControllerOfficial: public Controller
{
    public: static vector<Controller *> getAll(vector<Controller*> controllers);

    public: void startMonitoring();

    public: void stopMonitoring();

    public: void monitor();

    public: void rumbleMax();

    public: void rumbleVariable(unsigned char rumble);

    public: void rumbleOff();

    public: void setLeds(unsigned char mode);

    public: void close();

    bool isClosed();

    void setGeneralCallback(void (*generalCallback)(Controller *, ControllerStatus *, ControllerStatus *));

    uint8_t getControllerId();

private:
    XboxControllerOfficial(libusb_device_handle * h, int serialNumber);

    ControllerStatus * previous;
    ControllerStatus * current;

    libusb_device_handle * handle;

    void (*generalCallback)(Controller *, ControllerStatus *, ControllerStatus *);

    volatile bool monitoring;

    volatile bool closed;

    volatile bool doneClosing;

    int serialNumber;
};

#endif
