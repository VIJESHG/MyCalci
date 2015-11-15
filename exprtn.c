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
#include <stdio.h>
#include "stack.h"
#include <string.h>
#include <stdlib.h>
stack p;
cstack q;
Integer infix(char *arr) {
int precedance(char c);
void operation(char c);
	int k;
	int i = 0, j = 0, m, r, state = 0; 
	char c, d[2]; 
	char str[128];
	init(&p);
	cinit(&q);
	for(r = 0; r < 127; r++) {  							/* init string to zero */
		str[r] = '0';		
	}
	str[r] = '\0';	
	while(arr[i] != '\0'){
		switch(arr[i]){
			case '1': case'2': case '3': case '4':
			case '5': case'6': case '7': case '8':
			case '9': case'0':
			
				str[j] = arr[i];       					/* store digits in an array */
				state = 1;
				i++;
				j++;
				k = j;                					/* remember the last position to convert array into string */
				break;

			case'+':
				if(arr[i-1] != ')' && arr[i-1] != ' '){
					if(state == 1) {
						Integer I;
						j = 0;
						str[k] = '\0';           		/* convert digit array to string */
						I = CreateIntegerFromString(str);
						push(&p, I);
						state = 0;
					}
					else {
						for(r = 0; r < 127; r++){ 		/* init srting to zero */
							str[r] = '0';
						}	
						str[r] = '\0';
						Integer I;
						I = CreateIntegerFromString(str);
						push(&p, I);
					}
					
				}
				if(cisempty(&q) != 0){
					if(precedance(*ctop(&q)) <= 20)    		/* top operator has less or equal prec */
						cpush(&q, arr[i]);
					else {
						while(precedance(*ctop(&q)) > 20) {  /* solve untill we get smaller prec */
							operation(*ctop(&q));
							c = cpop(&q);                  /* pop solved operator */
						}
						cpush(&q, arr[i]);                   /* push curr oprtr */
					}
				}
				else
					cpush(&q, arr[i]);                        /* if curr oprtr is first push it */
				i++;
				break;
				
			case'-':
				if(arr[i-1] != ')' && arr[i-1] != ' '){
					if(state == 1) {
					Integer I;
					j = 0;
					str[k] = '\0';
					I = CreateIntegerFromString(str);
					push(&p, I);
					state = 0;
					}
					else {
						for(r = 0; r < 127; r++){
						str[r] = '0';
					}	
						str[r] = '\0';
						Integer I;
						I = CreateIntegerFromString(str);
						push(&p, I);
					}
				}
				if(cisempty(&q) != 0){
					if(precedance(*ctop(&q)) == 10)
						cpush(&q, arr[i]);
					else{
						while(precedance(*ctop(&q)) > 10){	
							operation(*ctop(&q));
							c = cpop(&q);
						}
						cpush(&q, arr[i]);
					}
				}
				else
					cpush(&q, arr[i]);
				i++;	
				break;
			case'%':
				if(arr[i-1] != ')' && arr[i-1] != ' '){
					j = 0;
					Integer I;
					str[k] = '\0';
					I = CreateIntegerFromString(str);
					push(&p, I);
					state = 0;
				}
				if(cisempty(&q) != 0){
					if(precedance(*ctop(&q)) <= 30)
						cpush(&q, arr[i]);
					else{
						while(precedance(*ctop(&q)) > 30){
							operation(*ctop(&q));
							c = cpop(&q);
						}
						cpush(&q, arr[i]);
					}
				}
				else
					cpush(&q, arr[i]);
				i++;
				break;
			
		
			case'*': 
				if(arr[i-1] != ')' && arr[i-1] != ' '){
				      j = 0;
					str[k] = '\0';
					Integer I;
					I = CreateIntegerFromString(str);
				     // PrintInteger(I);
					push(&p, I);
					state = 0;
				}
				if(cisempty(&q) != 0){
					if(precedance(*ctop(&q)) <= 40)
						cpush(&q, arr[i]);
					else{
						while(precedance(*ctop(&q)) > 40){	
						operation(*ctop(&q));
						c = cpop(&q);	
						}
						cpush(&q, arr[i]);
					}
				}
				else
					cpush(&q, arr[i]);
				i++;	
				break;
				
			case'/': 
				if(arr[i-1] != ')' && arr[i-1] != ' '){
					j = 0;
					str[k] = '\0';
					Integer I;
					I = CreateIntegerFromString(str);
				     // PrintInteger(I);
					push(&p, I);
					state = 0;
				}
				if(cisempty(&q) != 0){
					if(precedance(*ctop(&q)) <= 50)
						cpush(&q,arr[i]);
					else{
						while(precedance(*ctop(&q)) > 50){	
						operation(*ctop(&q));
						c = cpop(&q);	
						}
						cpush(&q, arr[i]);
					}
				}
				else
					cpush(&q, arr[i]);
				i++;	
				break;
			
			case'(':
				cpush(&q, arr[i]);              			/* opening brace */
				i++;
				break;
				
			case')':
				if(arr[i-1] != ')' && arr[i-1] != ' ') {
					j = 0;
					str[k] = '\0';
					Integer I;
					I = CreateIntegerFromString(str);
				      //PrintInteger(I);
					push(&p, I);
					state = 0;
				}
				while(*ctop(&q) != '(') {            		/* solve untill we get opening brace */
			        	operation(*ctop(&q));	
					c = cpop(&q);	
				}
				c = cpop(&q);                       		/* pop opening brace */
				i++;	
				break;
		
			case ' ':                                 		/* skip spaces */
			 	i++;				
			 	break;
			default:
				i++;
				printf("Invalid Expression\n");
				exit(1);
				break;
		}
	}
	
	if(arr[i] == '\0' && arr[i-1] != ')' && arr[i-1] != ' ') {
		str[k] = '\0';
		Integer I;
		I = CreateIntegerFromString(str);
		//PrintInteger(I);
		push(&p, I);
		state = 0;
	}
	while(cisempty(&q) != 0) {             					/* solve remaining */
				operation(*ctop(&q));
				c = cpop(&q);
	}
	return top(&p);
	
}

void operation(char c){
	Integer x,y,z;
	x = pop(&p);
	y = pop(&p);
	switch(c){	
		case'+':
			z = AddIntegers( x, y);
			push(&p, z);
			break;
		case'-':
			z = SubstractIntegers(y, x);
			push(&p, z);
			break;
		case '%':
			z = ModIntegers(y,x);
			push(&p, z);
			break;	
		case'*':
			z = MultiplyIntegers(x, y);
			push(&p, z);
			break;
		case'/':
			z = DivideIntegers(y,x);
			push(&p, z);
			break;
	}
}

int precedance(char c){
	if( c == '-')
		return 10;
	else if( c == '+')
		return 20;
	else if( c == '%')
		return 30;
	else if( c == '*')
		return 40;
	else if(c == '/')
		return 50;
	else if(c =='(')
		return 0;
}
