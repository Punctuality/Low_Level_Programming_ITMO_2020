all: run

run: main
	./main

main: main.o
	gcc -o main *.o

main.o: main.c mem.c mem_debug.c
	gcc -Wpedantic -Wall -Werror -c *.c

clean:
	rm -f *.o main