CC = g++
CFLAGS = -std=c++11 -O2 -pedantic -Wall -Werror -Wno-sign-compare

all:
	$(CC) $(CFLAGS) main.cpp -o main

clear:
	rm *.o main
