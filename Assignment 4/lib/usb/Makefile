CXXFLAGS= -I.
LIBS=-lrt
SOURCES=XboxControllerStatus.cpp XboxController.cpp XboxControllerOfficial.cpp ControllerStatus.cpp Controller.cpp
OUTPUT=${SOURCES:.cpp=.o}
OUTPUTLIB=libusb.a

target:
	arm-linux-g++ ${CXXFLAGS} -c ${SOURCES} ${LIBS}
	ar rvs ${OUTPUTLIB} ${OUTPUT}
	rm -rf ${OUTPUT}
clean:
	rm -rf ${OUTPUTLIB} 
