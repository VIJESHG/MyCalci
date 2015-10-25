#include<stdio.h>
#include"stack.h"

void init(stack *s){
	s->i = 0 ;
}
void push(stack *s,Integer num){
	s->arr[s->i] = num;	
	(s->i)++;
}
Integer pop(stack *s){
	Integer x;
	x = s->arr[(s->i)-1];
	(s->i)--;
	return x;
}
int isempty(stack *s) {
	return s->i;
}
int isfull(stack *s) {
	return s->i == MAX - 1;
}
Integer top(stack *s){
	return s->arr[(s->i)-1];
	
}
void cinit(cstack *t){
	t->i = 0 ;
}
void cpush(cstack *t,char c){
	t->carr[t->i] = c;	
	(t->i)++;
}
char cpop(cstack *t){
	char x;
	x = t->carr[(t->i)-1];
	(t->i)--;
	return x;
}
int cisempty(cstack *t) {
	return t->i;
}
int cisfull(cstack *t) {
	return t->i == MAX - 1;
}
char* ctop(cstack *t){
	return &(t->carr[(t->i)-1]);
	
}



