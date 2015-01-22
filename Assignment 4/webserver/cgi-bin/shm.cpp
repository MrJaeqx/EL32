#include <errno.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <Semaphore.h>
#include <SharedMemory.h>
#include <mqueue.h>
#include <iostream>

using namespace std;

Semaphore * sem;
SharedMemory * shm;

int main(int argc, char* argv[]) {
	sem = new Semaphore("ShmSem");
    sem->newSemaphore();
    cout << "sem opened" << endl;

    shm = new SharedMemory("Shm", 2048);
    cout << "shm opened" << endl;
	while(true)
	{
		cout << "calling semwait" << endl;
	    sem->waitSemaphore();

	    cout << shm->getData() << endl;

	    cout << "calling sempost" << endl;
	    sem->postSemaphore();
	    usleep(1000000);
	}
}