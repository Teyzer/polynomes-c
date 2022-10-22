.PHONY: all clean

all: clean polynome tests main afterhandclean
run: clean polynome tests main afterhandclean runner

polynome: polynome.c
	gcc -c -Wall polynome.c
	
tests: tests.c polynome.h
	gcc -c -Wall tests.c
	
main: main.c polynome.h tests.h
	gcc -o main polynome.o tests.o main.c -Wall

afterhandclean:
	rm -f *.o

runner:
	./main

clean: 
	rm -f *.o main