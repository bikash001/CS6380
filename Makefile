CC = g++
CFLAGS = -std=c++11
all: tsp.o implementation.o greedy.o
	$(CC) $(CFLAGS) -o tsp tsp.o implementation.o greedy.o

tsp.o: tsp.cpp
	$(CC) $(CFLAGS) -c tsp.cpp

implementation.o: implementation.cpp header.hpp
	$(CC) $(CFLAGS) -c implementation.cpp

greedy.o: greedy.cpp
	$(CC) $(CFLAGS) -c greedy.cpp

clean:
	rm tsp *.o