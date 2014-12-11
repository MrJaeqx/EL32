CFLAGS=-O2 -Wall -Werror
SOURCES=el32-assignment2.cpp ControllerStatus.cpp XboxController.cpp

target:
	'/media/lars/0ae1d340-06af-4860-8b6e-8b3f8158443c/buildroot/output/host/usr/bin/arm-linux-g++' ${CFLAGS} ${SOURCES} -I. -o el32-assignment2 -lrt -lusb-1.0 -lpthread

host:
	g++ ${CFLAGS} ${SOURCES} -I. -o el32-assignment2-host -lrt -lusb-1.0 -lpthread
