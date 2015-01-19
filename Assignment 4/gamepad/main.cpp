#include <errno.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <Controller.h>
#include <ControllerStatus.h>
#include <sys/fcntl.h>
#include <mqueue.h>
#include <vector>
#include <iostream>
using std::vector;
using namespace std;

#define BUFFERLENGTH 2048

void generalCallback(Controller * controller, ControllerStatus * previous, ControllerStatus * current);
void sendControllerUpdate();
int clientId;
mqd_t mqReceive;
mqd_t mqSend;
JsonSerializerClient js;
vector<Controller *> controllers;

int main(int argc, char* argv[]) {
    clientId = 0;

    struct mq_attr attr;
    attr.mq_msgsize = 2048;
    attr.mq_maxmsg = 8;
    mq_unlink("/controller_read");
    mq_unlink("/controller_write");
    mqSend = mq_open("/controller_read", O_CREAT | O_WRONLY, 0666, &attr);
    mqReceive = mq_open("/controller_write", O_CREAT | O_RDONLY | O_NONBLOCK, 0666, &attr);

    if (mqSend == -1 || mqReceive == -1) {
        perror("failed to open mq: ");
        exit(0);
    }

    controllers = Controller::getAll(controllers);
    while(true) {
        controllers = Controller::getAll(controllers);

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
        char bufferReceive[BUFFERLENGTH];
		
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
        }
    }
}

void sendControllerUpdate() {
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
}



void generalCallback(Controller *controller, ControllerStatus *previous, ControllerStatus *current) {
    cout << "sending update: " << endl;
    ClientInput* clientInput = new ClientInput();
    clientInput->setClientId(clientId);
    clientInput->setNumberControllers(controllers.size());

    bool start = false;
    bool back = false;
    bool enter = false;

    Direction direction = DEFAULT;
    if (current->getLeft())
    {
        direction = LEFT;
    }
    else if (current->getRight())
    {
        direction = RIGHT;
    } else
    {
        direction = STRAIGHT;
    }
	 
    if (previous->getStartButton() != current->getStartButton())
    {
        start = current->getStartButton();
    }
    else if (previous->getBackButton() != current->getBackButton())
    {
        back = current->getBackButton();
    }
    else if (previous->getEnterButton() != current->getEnterButton())
    {
        enter = current->getEnterButton();
    }
    ControllerInfo* controllerInfo = new ControllerInfo(controller->getControllerId(), start, enter, back, direction);
    clientInput->addControllerInfo(controllerInfo);
    char bufferSend[BUFFERLENGTH];
    string clientInputStr = js.convertClientInputToJson(clientInput);
    size_t clientInputSize = clientInputStr.copy(bufferSend, clientInputStr.size());
    bufferSend[clientInputSize] = '\0';
    cout << bufferSend << endl;
    mq_send(mqSend, bufferSend, BUFFERLENGTH, 1);
}
