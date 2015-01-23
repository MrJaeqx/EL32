#include <errno.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mqueue.h>
#include <iostream>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

using namespace std;

typedef struct
{
    // a data structure with 3 members
    bool rumble;
    unsigned char ledMode;
} MQ_REQUEST_MESSAGE;

static void 
getattr (mqd_t mq_fd)
{
    struct mq_attr      attr;
    int                 rtnval;
    
    rtnval = mq_getattr (mq_fd, &attr);
    if (rtnval == -1)
    {
        perror ("mq_getattr() failed");
    }
    fprintf (stderr, "%d: mqdes=%d max=%ld size=%ld nrof=%ld\n",
                getpid(), 
                mq_fd, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
}

int main(int argc, char* argv[]) {
    mqd_t       mq_fd = -1;
    struct      mq_attr attr;
    int         rtnval = -1;
    MQ_REQUEST_MESSAGE req;

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof (MQ_REQUEST_MESSAGE);

    cout << "Content-Type: text/plain" << endl << endl;

    string s = getenv("QUERY_STRING");
    string delimiter = "&";
    string r = s.substr(0, s.find(delimiter));
    string l = s.substr(s.find(delimiter)+1, s.length());

    req.rumble = false;
    req.ledMode = 1;

    if(r == "true")
    {
        req.rumble = true;
    }
    if(atoi(l.c_str()) > 0 && atoi(l.c_str()) < 6) {
        req.ledMode = atoi(l.c_str());
    }

	mq_fd = mq_open("/MQ1337", O_WRONLY | O_CREAT, 0666, &attr);
    if (mq_fd == (mqd_t)-1) {
        perror("mq_open()");
        exit(1);
    }

    getattr(mq_fd);

    cout << "mq opened"<< endl;

	// while(true)
	// {
		rtnval = mq_send (mq_fd, (char *) &req, sizeof (req), 0);

        getattr(mq_fd);
		if (rtnval == -1) {
        	perror("mq_send()");
        	exit(1);
        }
		cout << "sent message" << endl;
	//     usleep(1000000);
	// }
}