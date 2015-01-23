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

    shm = new SharedMemory("Shm", 2048);

    sem->waitSemaphore();

	cout << "Content-Type: application/json" << endl << endl;
    cout << shm->getData() << endl;

    sem->postSemaphore();

    return 0;
}