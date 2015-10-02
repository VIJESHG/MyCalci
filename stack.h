#define MAX 128
#include<stdio.h>
typedef struct stack{
	int i;
	double arr[MAX];
	} stack;
void init(stack* s);
void push(stack* s,double num);
double pop(stack* s);
int isfull(stack *s);
int isempty(stack *s);
double top(stack *s);

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
