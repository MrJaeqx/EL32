
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <Semaphore.h>
#include <cstdio> 

using namespace std;

Semaphore::Semaphore(char * name)
{
    strcpy(this->sem_name,name);
    semdes = SEM_FAILED;
}
     
void Semaphore::newSemaphore()
{
    if (semdes != SEM_FAILED)
    {
        cout << "ERROR: another semaphore already opened" << endl;
    }
    else
    {
        semdes = sem_open (sem_name, O_CREAT, 0600, 1);
        if (semdes == SEM_FAILED)
        {
            perror ("ERROR: sem_open() failed");
        }
    }
}

void Semaphore::openSemaphore()
{
    if (semdes != SEM_FAILED)
    {
        cout << "ERROR: another semaphore already opened" << endl;
    }
    else
    {
        semdes = sem_open (sem_name, 0);
        if (semdes == SEM_FAILED)
        {
            perror ("ERROR: sem_open() failed");
        }
    }
}

void Semaphore::closeSemaphore()
{
    if (semdes == SEM_FAILED)
    {
        cout << "ERROR: no open semaphore" << endl;
    }
    else
    {
        rtnval = sem_close (semdes);
        if (rtnval != 0)
        {
            perror ("ERROR: sem_close() failed");
        }
        semdes = SEM_FAILED; 
    }
}

void Semaphore::postSemaphore()
{
    if (semdes == SEM_FAILED)
    {
        cout << "ERROR: no open semaphore" << endl;
    }
    rtnval = sem_post (semdes);
    if (rtnval != 0)
    {
        perror ("ERROR: sem_post() failed");
    }
}

void Semaphore::waitSemaphore()
{
    if (semdes == SEM_FAILED)
    {
        cout << "ERROR: no open semaphore" << endl;
    }
    rtnval = sem_wait (semdes);
    if (rtnval != 0)
    {
        perror ("ERROR: sem_wait() failed");
    }
}
           
void Semaphore::unlinkSemaphore()
{
    rtnval = sem_unlink (sem_name);
    if (rtnval != 0)
    {
        perror ("ERROR: sem_unlink() failed");
    }
}