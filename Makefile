CC = g++
CFLAGS = -std=c++11
all: tsp.o implementation.o
	$(CC) -o tsp tsp.o implementation.o

tsp.o: tsp.cpp
	$(CC) $(CFLAGS) -c tsp.cpp

implementation.o: implementation.cpp header.hpp
	$(CC) $(CFLAGS) -c implementation.cpp

clear:
	rm tsp *.o