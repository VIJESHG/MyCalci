bc:main.o exprtn.o operations.o stack.o 
	cc main.o exprtn.o operations.o stack.o -o bc -lm
main.o:main.c operations.h
	cc -c main.c
operations.o:operations.c stack.h
	cc -c exprtn.c
exprtn.o:operations.c operations.h
	cc -c operations.c -lm
stack.o:stack.c stack.h
	cc -c stack.c
