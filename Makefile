
a:infixmain.o infix.o stack.o
	cc infixmain.o infix.o stack.o -o a
infixmain.o: infixmain.c stack.h
		cc -c infixmain.c
infix.o:infix.c stack.h
	cc -c infix.c
stack.o:stack.c stack.h
	cc -c stack.c

b: expomain.o expon.o
	cc  expomain.o expon.o -o b -lm
expomain.o: expomain.c 
	cc -c expomain.c
expon.o: expon.c
	cc -c expon.c
