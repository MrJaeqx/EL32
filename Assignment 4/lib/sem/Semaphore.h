#include <iostream>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <semaphore.h>

class Semaphore {
    public:
        Semaphore(char * name);
        void newSemaphore();
        void openSemaphore();
        void closeSemaphore();
        void postSemaphore();
        void waitSemaphore();
        void unlinkSemaphore();
    private:
        sem_t *  semdes;
        int             rtnval;
        char            sem_name[80];
};
