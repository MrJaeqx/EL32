CFLAGS=-O2 -Wall
LIBPATH= -L../lib/usb -I../lib/usb
SOURCES=main.cpp
LIBS=-lrt -lpthread -lusb-1.0 -lusb
OUTPUT=gamepad.out

target:
	arm-linux-g++ ${CFLAGS} -o ${OUTPUT} ${SOURCES} ${LIBPATH}   ${LIBS}

clean:
	rm -rf ${OUTPUT}
