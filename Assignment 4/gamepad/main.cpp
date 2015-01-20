#include <errno.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <XboxController.h>
#include <ControllerStatus.h>
#include <sys/fcntl.h>
#include <mqueue.h>
#include <vector>
#include <iostream>
using std::vector;
using namespace std;


void generalCallback(XboxController * controller, ControllerStatus * previous, ControllerStatus * current);
void sendControllerUpdate();
int clientId;
vector<XboxController *> controllers;

int main(int argc, char* argv[]) {
    clientId = 0;

    controllers = XboxController::getAll(controllers);
    while(true) {
        controllers = XboxController::getAll(controllers);

        for (unsigned int i = 0; i < controllers.size(); i++) {
            if (controllers[i]->isClosed()) {
                printf("closed\n");
                controllers.erase(controllers.begin() + i);
                sendControllerUpdate();
            }
        }
        for (unsigned int i = 0; i < controllers.size(); i++) {
            controllers[i]->setGeneralCallback(generalCallback);
            controllers[i]->startMonitoring();
        }

		/*
        int result = mq_receive(mqReceive, bufferReceive, BUFFERLENGTH, NULL);
        if (result != -1) {
            bufferReceive[result] = '\0';
            cout << "msq received: " << bufferReceive << endl;
            ServerToClientMessage* sm = new ServerToClientMessage();
            sm = js.convertJsonToServerToClientMessage(bufferReceive);
            if (sm->getClientId() != 0) {
                clientId = sm->getClientId();
                sendControllerUpdate();
            }
            vector<ControllerCommand *> controllerCommands;
            controllerCommands = sm->getControllerCommands();

            for (unsigned int i = 0; i < controllerCommands.size(); i++) {
                for(unsigned int j = 0; j < controllers.size(); j++) {
                    if(controllerCommands[i]->getControllerId() == controllers[j]->getControllerId())
                    {
                        controllers[j]->setLeds(controllerCommands[i]->getLedCircle());
                        controllers[j]->rumbleVariable(controllerCommands[i]->getVibrate());
                    }
                }
            }
            cout << "msq received end" << endl;
        }*/
    }
}

void sendControllerUpdate() {
    /*
    cout << "Sending controller update" << endl;
    ClientInput* ci = new ClientInput();
    ci->setNumberControllers(controllers.size());
    ci->setClientId(clientId);
    for(unsigned int i = 0; i < controllers.size(); i++)
    {
        ControllerInfo* info = new ControllerInfo(controllers[i]->getControllerId(), false, false, false, DEFAULT);
        ci->addControllerInfo(info);
    }
    ci->setSyncPlayers(true);
    char buffer[BUFFERLENGTH];
    string clientInputString = js.convertClientInputToJson(ci);
    size_t clientInputLength = clientInputString.copy(buffer, clientInputString.size());
    buffer[clientInputLength] = '\0';
    cout << buffer << endl;
    mq_send(mqSend, buffer, BUFFERLENGTH, 1);
    */

    //caller->rumbleMax();
    //caller->setLeds(ROTATING);
    cout << "MQ Stuff" << endl;
}

void generalCallback(XboxController * caller, ControllerStatus * previous, ControllerStatus * current)
{

    cout << dec << (int) caller->getControllerId() << " "; 

    if (!previous->getButtonA() && current->getButtonA())
    {
        cout << "A pressed" << endl;
    }
    else if (previous->getButtonA() && !current->getButtonA())
    {
        cout << "A released" << endl;
    }
    else if (!previous->getButtonX() && current->getButtonX())
    {
        cout << "X pressed" << endl;
    }
    else if (previous->getButtonX() && !current->getButtonX())
    {
        cout << "X released" << endl;
    }
    else if (!previous->getButtonY() && current->getButtonY())
    {
        cout << "Y pressed" << endl;
    }
    else if (previous->getButtonY() && !current->getButtonY())
    {
        cout << "Y released" << endl;
    }
    else if (!previous->getButtonB() && current->getButtonB())
    {
        cout << "B pressed" << endl;
    }
    else if (previous->getButtonB() && !current->getButtonB())
    {
        cout << "B released" << endl;
    }
    else if (!previous->getDPadUp() && current->getDPadUp())
    {
        cout << "DPad Up pressed" << endl;
    }
    else if (previous->getDPadUp() && !current->getDPadUp())
    {
        cout << "DPad Up released" << endl;
    }
    else if (!previous->getDPadDown() && current->getDPadDown())
    {
        cout << "DPad Down pressed" << endl;
    }
    else if (previous->getDPadDown() && !current->getDPadDown())
    {
        cout << "DPad Down released" << endl;
    }
    else if (!previous->getDPadLeft() && current->getDPadLeft())
    {
        cout << "DPad Left pressed" << endl;
    }
    else if (previous->getDPadLeft() && !current->getDPadLeft())
    {
        cout << "DPad Left released" << endl;
    }
    else if (!previous->getDPadRight() && current->getDPadRight())
    {
        cout << "DPad Right pressed" << endl;
    }
    else if (previous->getDPadRight() && !current->getDPadRight())
    {
        cout << "DPad Right released" << endl;
    }
    else if (!previous->getStartButton() && current->getStartButton())
    {
        cout << "Start pressed" << endl;
    }
    else if (previous->getStartButton() && !current->getStartButton())
    {
        cout << "Start released" << endl;
    }
    else if (!previous->getBackButton() && current->getBackButton())
    {
        cout << "Back pressed" << endl;
    }
    else if (previous->getBackButton() && !current->getBackButton())
    {
        cout << "Back released" << endl;
    }
    else if (!previous->getLeftStickPress() && current->getLeftStickPress())
    {
        cout << "Left stick pressed" << endl;
    }
    else if (previous->getLeftStickPress() && !current->getLeftStickPress())
    {
        cout << "Left stick released" << endl;
    }
    else if (!previous->getRightStickPress() && current->getRightStickPress())
    {
        cout << "Right stick pressed" << endl;
    }
    else if (previous->getRightStickPress() && !current->getRightStickPress())
    {
        cout << "Right stick released" << endl;
    }
    else if (!previous->getButtonLB() && current->getButtonLB())
    {
        cout << "Left back button pressed" << endl;
    }
    else if (previous->getButtonLB() && !current->getButtonLB())
    {
        cout << "Left back button released" << endl;
    }
    else if (!previous->getButtonRB() && current->getButtonRB())
    {
        cout << "Right back button pressed" << endl;
    }
    else if (previous->getButtonRB() && !current->getButtonRB())
    {
        cout << "Right back button released" << endl;
    }
    else if (!previous->getButtonXboxButton() && current->getButtonXboxButton())
    {
        cout << "Xbox button pressed" << endl;
    }
    else if (previous->getButtonXboxButton() && !current->getButtonXboxButton())
    {
        cout << "Xbox button released" << endl;
    }
    else if (previous->getLeftTrigger() != current->getLeftTrigger())
    {
        cout << "Left trigger: " << hex << (int) current->getLeftTrigger() << endl;
    }
    else if (previous->getRightTrigger() != current->getRightTrigger())
    {
        cout << "Right trigger: " << hex << (int) current->getRightTrigger() << endl;
    }
    else if (abs(previous->getLeftStickXAxis() - current->getLeftStickXAxis()) > 100)
    {
        cout << "Left stick x axis: " << hex << (int16_t) current->getLeftStickXAxis() << endl;
    }
    else if (abs(previous->getLeftStickYAxis() - current->getLeftStickYAxis()) > 100)
    {
        cout << "Left stick y axis: " << hex << (int16_t) current->getLeftStickYAxis() << endl;
    }
    else if (abs(previous->getRightStickXAxis() - current->getRightStickXAxis()) > 100)
    {
        cout << "Right stick x axis: " << hex << (int16_t) current->getRightStickXAxis() << endl;
    }
    else if (abs(previous->getRightStickYAxis() - current->getRightStickYAxis()) > 100)
    {
        cout << "Right stick y axis: " << hex << (int16_t) current->getRightStickYAxis() << endl;
    }

}
