# P=helloworld
# OBJECTS=helloworld.c square.c shape.c
CFLAGS = -g -Wall --std=c99
LDLIBS=
CC=gcc
# $(P): $(OBJECTS)

helloworld : main.o shape.o square.o
	$(CC) -o helloworld.out main.o shape.o square.o

main : main.c shape.c square.c
	$(CC) -c main.c shape.c square.c

clean :
	rm helloworld.out *.o