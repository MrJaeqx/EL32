#include <errno.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mqueue.h>
#include <iostream>

using namespace std;

struct mq_attr attr;

int main(int argc, char* argv[]) {
	attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 2048;
    attr.mq_curmsgs = 0;

    mq_unlink("/MQ2");
	mqd_t smqClientSend = mq_open("/MQ2", O_CREAT | O_WRONLY, 0666, &attr);
    if (smqClientSend == (mqd_t)-1 || smqClientSend == NULL) {
        perror("mq_open()");
        exit(1);
    }
    cout << "mq opened" << endl;


	while(true)
	{
		mqd_t mqs = mq_send(smqClientSend, "T", 2048, 0);
		if (mqs == (mqd_t)-1) {
        	perror("mq_send()");
        	exit(1);
        }
		cout << "sent message" << endl;
	    usleep(1000000);
	}
}