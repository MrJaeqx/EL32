CFLAGS=-O2 -Wall
LIBPATH= -L../../lib/json -L../../lib/usb -I../../lib/usb -L../../lib/tcp -I../../lib/tcp -I../../lib/client-server -I../../lib/json/include -L../../lib/client-server
SOURCES=main.cpp
LIBS=-lrt -lpthread -lusb-1.0 -lusb
OUTPUT=USB.out

target:
	arm-linux-g++ ${CFLAGS} -o ${OUTPUT} ${SOURCES} ${LIBPATH}   ${LIBS}

clean:
	rm -rf ${OUTPUT}
