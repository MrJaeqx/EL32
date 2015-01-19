SOURCES=SharedMemory.cpp
OUTPUTTARGET=SharedMemory.o
OUTPUTHOST=SharedMemoryHost.o

target:
	arm-linux-g++ -o ${OUTPUTTARGET} -c ${SOURCES} -I. -lrt
	ar rvs libshm.a ${OUTPUTTARGET}

host:
	g++ -o ${OUTPUTHOST} -c ${SOURCES} -I. -lrt 
	ar rvs libshmHost.a ${OUTPUTHOST}

clean:
	rm ${OUTPUTTARGET} ${OUTPUTHOST}
