#ifndef __Controller_h__
#define __Controller_h__

#include "ControllerStatus.h"
#include <vector>
#include <stdint.h>

using namespace std;
class ControllerStatus;
class Controller
{
public:
    static vector<Controller *> getAll(vector<Controller*> controllers);
    public: virtual void startMonitoring() = 0;

    public: virtual void stopMonitoring() = 0;

    public: virtual void monitor() = 0;

    public: virtual void rumbleMax() = 0;

    public: virtual void rumbleVariable(unsigned char rumble) = 0;

    public: virtual void rumbleOff() = 0;

    public: virtual void setLeds(unsigned char mode) = 0;

    public: virtual void close() = 0;

    virtual void setGeneralCallback(void (*generalCallback)(Controller *, ControllerStatus *, ControllerStatus *)) = 0;
    virtual bool isClosed() = 0;
    virtual uint8_t getControllerId() = 0;
};

#endif
