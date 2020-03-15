# P=helloworld
# OBJECTS=helloworld.c square.c shape.c
CFLAGS = -g -Wall --std=c99 `pkg-config --cflags gsl`
LDLIBS=`pkg-config --libs gsl`
CC=gcc
# $(P): $(OBJECTS)

helloworld : main.o shape.o square.o
	$(CC) $(LDLIBS) -o helloworld.out main.o shape.o square.o $(LDLIBS)

main : main.c shape.c square.c
	$(CC) -c main.c shape.c square.c

clean :
	rm helloworld.out *.o