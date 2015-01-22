#include <errno.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <XboxController.h>
#include <ControllerStatus.h>
#include <Semaphore.h>
#include <SharedMemory.h>
#include <sys/fcntl.h>
#include <mqueue.h>
#include <vector>
#include <iostream>
#include <sstream>
using std::vector;
using namespace std;


void generalCallback(XboxController * controller, ControllerStatus * previous, ControllerStatus * current);
int clientId;
vector<XboxController *> controllers;
Semaphore * sem;
SharedMemory * shm;
pthread_t messageQueueListenerThread;
struct mq_attr attr;

int dPadUp, dPadDown, dPadLeft, dPadRight, startBtn, backBtn, lsP, rsP, lbBtn, rbBtn, xboxBtn, aBtn, bBtn, xBtn, yBtn;
uint8_t lTrg, rTrg;
int16_t lXaxis, lYaxis, rXaxis, rYaxis;



// message queue listener
void* messageQueueListener(void* argument) {
    
    // read message queue and send to all clients
    mqd_t messageQueueIDReceiver = mq_open("/MQ", O_RDONLY | O_CREAT, 0644, &attr);
    if (messageQueueIDReceiver == (mqd_t)-1) {
        perror("Receiver: mq_open()");
        exit(1);
    }       
    
    // buffer
    char buffer[2048];      
        
    // loop
    while(true){   
        ssize_t bytes_read;
        
        // receive message, blocks till a new message is received
        bytes_read = mq_receive(messageQueueIDReceiver, buffer, 2048, 0);                    
        buffer[bytes_read] = '\0';  
        
        
        std::cout << "Message Received :" << buffer << std::endl; 
        
    }
}

void sendMQUpdateToControllers(vector<XboxController *> ctrls, bool rumble, unsigned char ledMode) {
    for (unsigned int i = 0; i < ctrls.size(); i++) {
        if(rumble){
            ctrls[i]->rumbleMax();
        }
        else
        {
            ctrls[i]->rumbleOff();
        }   
        ctrls[i]->setLeds(ledMode);
    }
    cout << "MQ Stuff" << endl;
}

void generalCallback(XboxController * caller, ControllerStatus * previous, ControllerStatus * current)
{
    sem->waitSemaphore();

    cout << dec << (int) caller->getControllerId() << " "; 

    if (!previous->getButtonA() && current->getButtonA())
    {
        aBtn = 1;
        cout << "A pressed" << endl;
    }
    else if (previous->getButtonA() && !current->getButtonA())
    {
        aBtn = 0;
        cout << "A released" << endl;
    }
    else if (!previous->getButtonX() && current->getButtonX())
    {
        xBtn = 1;
        cout << "X pressed" << endl;
    }
    else if (previous->getButtonX() && !current->getButtonX())
    {
        xBtn = 0;
        cout << "X released" << endl;
    }
    else if (!previous->getButtonY() && current->getButtonY())
    {
        yBtn = 1;
        cout << "Y pressed" << endl;
    }
    else if (previous->getButtonY() && !current->getButtonY())
    {
        yBtn = 0;
        cout << "Y released" << endl;
    }
    else if (!previous->getButtonB() && current->getButtonB())
    {
        bBtn = 1;
        cout << "B pressed" << endl;
    }
    else if (previous->getButtonB() && !current->getButtonB())
    {
        bBtn = 0;
        cout << "B released" << endl;
    }
    else if (!previous->getDPadUp() && current->getDPadUp())
    {
        dPadUp = 1;
        cout << "DPad Up pressed" << endl;
    }
    else if (previous->getDPadUp() && !current->getDPadUp())
    {
        dPadUp = 0;
        cout << "DPad Up released" << endl;
    }
    else if (!previous->getDPadDown() && current->getDPadDown())
    {
        dPadDown = 1;
        cout << "DPad Down pressed" << endl;
    }
    else if (previous->getDPadDown() && !current->getDPadDown())
    {
        dPadDown = 0;
        cout << "DPad Down released" << endl;
    }
    else if (!previous->getDPadLeft() && current->getDPadLeft())
    {
        dPadLeft = 1;
        cout << "DPad Left pressed" << endl;
    }
    else if (previous->getDPadLeft() && !current->getDPadLeft())
    {
        dPadLeft = 0;
        cout << "DPad Left released" << endl;
    }
    else if (!previous->getDPadRight() && current->getDPadRight())
    {
        dPadRight = 1;
        cout << "DPad Right pressed" << endl;
    }
    else if (previous->getDPadRight() && !current->getDPadRight())
    {
        dPadRight = 0;
        cout << "DPad Right released" << endl;
    }
    else if (!previous->getStartButton() && current->getStartButton())
    {
        startBtn = 1;
        cout << "Start pressed" << endl;
    }
    else if (previous->getStartButton() && !current->getStartButton())
    {
        startBtn= 0;
        cout << "Start released" << endl;
    }
    else if (!previous->getBackButton() && current->getBackButton())
    {
        backBtn = 1;
        cout << "Back pressed" << endl;
    }
    else if (previous->getBackButton() && !current->getBackButton())
    {
        backBtn = 0;
        cout << "Back released" << endl;
    }
    else if (!previous->getLeftStickPress() && current->getLeftStickPress())
    {
        lsP = 1;
        cout << "Left stick pressed" << endl;
    }
    else if (previous->getLeftStickPress() && !current->getLeftStickPress())
    {
        lsP = 0;
        cout << "Left stick released" << endl;
    }
    else if (!previous->getRightStickPress() && current->getRightStickPress())
    {
        rsP = 1;
        cout << "Right stick pressed" << endl;
    }
    else if (previous->getRightStickPress() && !current->getRightStickPress())
    {
        rsP = 0;
        cout << "Right stick released" << endl;
    }
    else if (!previous->getButtonLB() && current->getButtonLB())
    {
        lbBtn = 1;
        cout << "Left back button pressed" << endl;
    }
    else if (previous->getButtonLB() && !current->getButtonLB())
    {
        lbBtn = 0;
        cout << "Left back button released" << endl;
    }
    else if (!previous->getButtonRB() && current->getButtonRB())
    {
        rbBtn = 1;
        cout << "Right back button pressed" << endl;
    }
    else if (previous->getButtonRB() && !current->getButtonRB())
    {
        rbBtn = 0;
        cout << "Right back button released" << endl;
    }
    else if (!previous->getButtonXboxButton() && current->getButtonXboxButton())
    {
        xboxBtn = 1;
        cout << "Xbox button pressed" << endl;
    }
    else if (previous->getButtonXboxButton() && !current->getButtonXboxButton())
    {
        xboxBtn = 0;
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

    stringstream ss;

    ss << "{";
        ss << "'dpad':{";
            ss << "'up':" << dPadUp << ",";
            ss << "'down':" << dPadDown << ",";
            ss << "'left':" << dPadLeft << ",";
            ss << "'right':" << dPadRight << "},";
        ss << "'start:'" << startBtn << ",";
        ss << "'back:'" << backBtn << ",";
        ss << "'xbox:'" << xboxBtn << ",";
        ss << "'leftstick':{";
            ss << "'press:'" << lsP << ",";
            ss << "'x:'" << hex << (int16_t) current->getLeftStickXAxis() << ",";
            ss << "'y:'" << hex << (int16_t) current->getLeftStickYAxis() << "},";
        ss << "'rightstick':{";
            ss << "'press:'" << rsP << ",";
            ss << "'x:'" << hex << (int16_t) current->getRightStickXAxis() << ",";
            ss << "'y:'" << hex << (int16_t) current->getRightStickYAxis() << "},";
        ss << "'a:'" << aBtn << ",";
        ss << "'b:'" << bBtn << ",";
        ss << "'x:'" << xBtn << ",";
        ss << "'y:'" << yBtn << ",";
        ss << "'leftback:'" << lbBtn << ",";
        ss << "'rightback:'" << rbBtn << ",";
        ss << "'lefttrigger:'" << hex << (int) current->getLeftTrigger() << ",";
        ss << "'righttrigger:'" << hex << (int) current->getRightTrigger();
    ss << "}" << endl;

    string buf = ss.str();

    shm->setData(buf.c_str());

    sem->postSemaphore();

}

int main(int argc, char* argv[]) {
    // set message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 2048;
    attr.mq_curmsgs = 0;  

    clientId = 0;
    dPadUp = dPadDown = dPadLeft = dPadRight = startBtn = backBtn = lsP = rsP = lbBtn = rbBtn = xboxBtn = aBtn = bBtn = xBtn = yBtn = 0;
    lTrg = rTrg = 0;
    lXaxis = lYaxis = rXaxis = rYaxis = 0;

    sem = new Semaphore("ShmSem");
    sem->newSemaphore();
    cout << "sem opened" << endl;

    shm = new SharedMemory("Shm", 2048);
    cout << "shm opened" << endl;

    // queue thread
    if(pthread_create(&messageQueueListenerThread, NULL, messageQueueListener, NULL)) {     
        perror("Error creating thread messageQueueListener");
    }
    cout << "mq thread made" << endl;

    controllers = XboxController::getAll(controllers);
    while(true) {
        controllers = XboxController::getAll(controllers);

        for (unsigned int i = 0; i < controllers.size(); i++) {
            if (controllers[i]->isClosed()) {
                printf("closed\n");
                controllers.erase(controllers.begin() + i);
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