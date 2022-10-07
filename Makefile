.PHONY: all clean

all: polynome tests main afterhandclean
run: polynome tests main afterhandclean runner

polynome: polynome.c
	gcc -c polynome.c
	
tests: tests.c polynome.h
	gcc -c tests.c
	
main: main.c polynome.h tests.h
	gcc -o main polynome.o tests.o main.c 

afterhandclean:
	rm -f *.o

runner:
	./main

clean: 
	rm -f *.o main