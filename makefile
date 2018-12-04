#
## CSCI 370 S10: Sample Makefile for OCCI compilation
#

CFLAGS = -I/usr/local/lib/Oracle/instantclient_11_2/sdk/include
LFLAGS = -L/usr/local/lib/Oracle/instantclient_11_2 -locci -lociei
all: example

example.o: example.cpp
	g++ -c $(CFLAGS) example.cpp

example: example.o
	g++ $(LFLAGS) -o example example.o

clean:
	rm *.o example

