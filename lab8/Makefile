CC=gcc
ASM=nasm
CFLAGS=-std=gnu99 -lm
AFLAGS=-felf64

all: run

run: main
	./main

main: clean main.o sepia.o bmp.o sse.o
	$(CC) $(CFLAGS) -o main main.o sepia.o bmp.o sse.o

main.o:
	$(CC) $(CFLAGS) -c main.c

sse.o:
	$(ASM) $(AFLAGS) -o sse.o sse.asm

sepia.o:
	$(CC) $(CFLAGS) -c sepia.c

bmp.o:
	$(CC) $(CFLAGS) -c bmp.c

clean:
	rm -rf main *.o
