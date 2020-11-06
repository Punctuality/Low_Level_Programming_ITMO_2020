all: run

run: main
	./main

main: main.o
	gcc -o main *.o

main.o: main.c bmp.c image.c clean
	gcc -pedantic-errors -Wall -Werror -c *.c

clean:
	rm -f *.o main