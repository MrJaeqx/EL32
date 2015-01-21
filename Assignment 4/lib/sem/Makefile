SOURCES=Semaphore.cpp
OUTPUTTARGET=Semaphore.o
OUTPUTHOST=SemaphoreHost.o

target:
	arm-linux-g++ -o ${OUTPUTTARGET} -c ${SOURCES} -I. -lrt
	ar rvs libsem.a ${OUTPUTTARGET}

host:
	g++ -o ${OUTPUTHOST} -c ${SOURCES} -I. -lrt 
	ar rvs libsemHost.a ${OUTPUTHOST}

clean:
	rm ${OUTPUTTARGET} ${OUTPUTHOST}
