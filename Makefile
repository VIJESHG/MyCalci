bc:main.o infix.o integer.o stack.o 
	cc main.o infix.o integer.o stack.o -o bc -lm
main.o:main.c integer.h
	cc -c main.c
infix.o:infix.c stack.h
	cc -c infix.c
integer.o:integer.c integer.h
	cc -c integer.c -lm
stack.o:stack.c stack.h
	cc -c stack.c
