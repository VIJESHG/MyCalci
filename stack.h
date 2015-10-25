#define MAX 128
#include<stdio.h>
#include "integer.h"
typedef struct stack{
	int i;
	Integer arr[MAX];
} stack;
void init(stack* s);
void push(stack* s,Integer num);
Integer pop(stack* s);
int isfull(stack *s);
int isempty(stack *s);
Integer top(stack *s);

typedef struct cstack{
	int i;
	char carr[MAX];
} cstack;
void cinit(cstack* t);
void cpush(cstack* t,char c);
char cpop(cstack* t);
int cisfull(cstack *t);
int cisempty(cstack *t);
char* ctop(cstack *t);
