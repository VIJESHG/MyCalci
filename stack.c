/*****************************************************************************
 * Copyright (C) Vijesh B.G. vijay.ghandare@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
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


