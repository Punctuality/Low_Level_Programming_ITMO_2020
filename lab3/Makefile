all: main

main: main.o
	gcc -o main main.o && ./main

main.o: main.c clean
	gcc --ansi -pedantic-errors -Wall -Werror -c -o main.o main.c

clean:
	rm -f main.o main
