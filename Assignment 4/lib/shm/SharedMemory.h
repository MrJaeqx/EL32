class SharedMemory {
public:
    SharedMemory(char * name, int size);
    SharedMemory(char * name);
    char * getData();
    void setData(const char * data);
    void closeMemory();
    void unlink();
private:
    char * create(char * name, int size);
    char * open(char * name);
    int shm_fd;
    char * data;
    char * name;
};
