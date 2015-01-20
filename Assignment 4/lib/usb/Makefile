CXXFLAGS= -I.
LIBS=-lrt
SOURCES=ControllerStatus.cpp XboxController.cpp
OUTPUT=${SOURCES:.cpp=.o}
OUTPUTLIB=libusb.a

target:
	arm-linux-g++ ${CXXFLAGS} -c ${SOURCES} ${LIBS}
	ar rvs ${OUTPUTLIB} ${OUTPUT}
	rm -rf ${OUTPUT}
clean:
	rm -rf ${OUTPUTLIB} 
