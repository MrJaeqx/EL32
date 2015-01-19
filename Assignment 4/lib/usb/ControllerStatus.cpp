#include "ControllerStatus.h"

bool ControllerStatus::compare(ControllerStatus *previous, ControllerStatus *current) {
    bool difference = false;

    if (previous->getLeft() != current->getLeft())
    {
        difference = true;
    }
    else if (previous->getRight() != current->getRight())
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
    else if (previous->getEnterButton() != current->getEnterButton())
    {
        difference = true;
    }
    return difference;
}
