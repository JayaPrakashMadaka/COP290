CC=g++

CFLAGS=-c -Wall

all:main

main: 
	$(CC)  -c -fpic libaudio.cpp
	$(CC) -shared -o libaudio.so libaudio.o
	$(CC) -L/$(LD_LIBRARY_PATH) -Wl,-rpath=$(LD_LIBRARY_PATH) -o yourcode.out main.cpp -laudio -L/$(MKL_BLAS_PATH)/include -I/$(MKL_BLAS_PATH)/lib -lpthread -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lm -ldl

	
clean:
	rm -rf  yourcode.out
