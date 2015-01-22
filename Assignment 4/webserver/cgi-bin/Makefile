CFLAGS=-O2 -Wall
LIBPATH= -L../../lib/usb -I../../lib/usb -L../../lib/sem -I../../lib/sem -L../../lib/shm -I../../lib/shm
LIBS=-lrt -lpthread -lusb-1.0 -lusb -lsem -lshm

target:
	arm-linux-g++ ${CFLAGS} -o mq.out messagequeue.cpp ${LIBPATH}   ${LIBS}
	arm-linux-g++ ${CFLAGS} -o shm.out shm.cpp ${LIBPATH}   ${LIBS}

clean:
	rm -rf ${OUTPUT}
