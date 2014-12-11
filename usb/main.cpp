#include "ControllerStatus.h"
#include "XboxController.h"
#include <unistd.h>

int main(void) {
    XboxController* controller = XboxController::getSingle();
    controller->startMonitoring();
    for (int i = 0; i < 5; i++) {
        sleep(1);
        controller->rumbleMax();
        sleep(1);
        controller->rumbleOff();
    }
    controller->close();
    return 0;
}
