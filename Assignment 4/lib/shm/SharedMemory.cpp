#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <SharedMemory.h>

char *
SharedMemory::create (char * shm_name, int size)
{
    int     rtnval;
    char *  shm_addr;
    
    printf ("Calling shm_open('%s')\n", shm_name);
    shm_fd = shm_open (shm_name, O_CREAT | O_RDWR, 0600);
    if (shm_fd == -1)
    {
        perror ("ERROR: shm_open() failed");
    }
    rtnval = ftruncate (shm_fd, size);
    if (rtnval != 0)
    {
        perror ("ERROR: ftruncate() failed");
    }

    shm_addr = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED)
    {
        perror ("ERROR: mmap() failed");
    }

    return (shm_addr);
}

char *
SharedMemory::open (char * shm_name)
{
    int     size;
    char *  shm_addr;

    printf ("Calling shm_open('%s')\n", shm_name);
    shm_fd = shm_open (shm_name, O_RDWR, 0600);
    if (shm_fd == -1)
    {
        perror ("ERROR: shm_open() failed");
    }
    size = lseek (shm_fd, 0, SEEK_END);

    shm_addr = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED)
    {
        perror ("ERROR: mmap() failed");
    }

    return (shm_addr);
}

SharedMemory::SharedMemory(char * name, int size) : shm_fd(-1) {
    data = create(name, size);
    this->name = name;
}

char * SharedMemory::getData() {
    return data;
}

void SharedMemory::closeMemory() {
    int rtnval = close(shm_fd);
    if (rtnval != 0)
    {
        perror ("ERROR: close() failed");
    }
}

void SharedMemory::unlink() {
    int rtnval = shm_unlink (name);
    if (rtnval != 0)
    {
        perror ("ERROR: shm_unlink() failed");
    }
}
