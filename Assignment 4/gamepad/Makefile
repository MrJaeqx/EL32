CFLAGS=-O2 -Wall
LIBPATH= -L../lib/usb -I../lib/usb -L../lib/sem -I../lib/sem -L../lib/shm -I../lib/shm
SOURCES=main.cpp
LIBS=-lrt -lpthread -lusb-1.0 -lusb -lsem -lshm
OUTPUT=gamepad.out

target:
	arm-linux-g++ ${CFLAGS} -o ${OUTPUT} ${SOURCES} ${LIBPATH}   ${LIBS}

clean:
	rm -rf ${OUTPUT}
