bc:main.o exprtn.o operations.o stack.o 
	cc main.o exprtn.o operations.o stack.o -o bc -lm
main.o:main.c operations.h
	cc -c main.c
infix.o:infix.c stack.h
	cc -c exprtn.c
integer.o:operations.c operations.h
	cc -c operations.c -lm
stack.o:stack.c stack.h
	cc -c stack.c
