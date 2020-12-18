all: run

run: main
	./main

main: main.o
	gcc -o main *.o -lm

main.o: main.c bmp.c image.c clean
	gcc -lm -pedantic-errors -Wall -Werror -c *.c

clean:
	rm -f *.o main