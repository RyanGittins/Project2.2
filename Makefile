#####################################################################
# Ryan Gittins
# Phil Sime
# 2013-10-26
#
# CS 441/541 : Project 2 Part 2
#
#####################################################################
#
# Type "make" or "make stoplight" to compile your code
# Type "make clean" to remove the executable (and any object files)
#
#####################################################################

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lpthread -lm

PROGS=stoplight

all: $(PROGS)

stoplight: support.o semaphore_support.o stoplight.c stoplight.h
	$(CC) -o stoplight stoplight.c support.o semaphore_support.o $(CFLAGS) $(LDFLAGS)

support.o: support.c support.h
	$(CC) -c -o support.o support.c $(CFLAGS)

semaphore_support.o: semaphore_support.h semaphore_support.c
	$(CC) -c -o semaphore_support.o semaphore_support.c $(CFLAGS)

clean:
	$(RM) $(PROGS) *.o
	$(RM) -rf *.dSYM
