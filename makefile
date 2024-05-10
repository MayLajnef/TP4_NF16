CC = gcc
CFLAGS = -lm -Wall 

.PHONY: all clean

default: all

all: main

main: main.c tp4.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f main
