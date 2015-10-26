#include <stdio.h>
#include "stack.h"
#include <string.h>
#include <stdlib.h>
stack p;
cstack o;
Integer infix(char *arr){
int precedance(char c);
void operation(char c);
	int k;
	int i = 0,j = 0,m,r,state = 0; 
	char c,d[2];
	char str[128];
	init(&p);
	cinit(&o);
	for(r = 0; r < 127; r++){
		str[r] = '0';
	}
	str[r] = '\0';	
	while(arr[i] != '\0'){
		switch(arr[i]){
			case '1': case'2': case '3': case '4':
			case '5': case'6': case '7': case '8':
			case '9': case'0':
			
				str[j] = arr[i];
				state = 1;
				i++;
				j++;
				k = j;
				break;

			case'+':
				if(arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ',' ){
					if(state == 1) {
					Integer I;
					j = 0;
					str[k] = '\0';
					I = CreateIntegerFromString(str);
				      //PrintInteger(I);
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
						//printf("a->");
				      	//PrintInteger(I);
						push(&p, I);
					}
					
				}
				if(cisempty(&o) != 0){
					if(precedance(*ctop(&o)) <= 20)
						cpush(&o, arr[i]);
					else{
						while(precedance(*ctop(&o)) > 20){
							operation(*ctop(&o));
							c = cpop(&o);
						}
						cpush(&o, arr[i]);
					}
				}
				else
					cpush(&o, arr[i]);
				i++;
				break;
				
			case'-':
				if(arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ','){
					if(state == 1) {
					Integer I;
					j = 0;
					str[k] = '\0';
					I = CreateIntegerFromString(str);
					//printf("in-->");
				    //PrintInteger(I);
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
						//printf("a->");
				      	//PrintInteger(I);
						push(&p, I);
					}
				}
				if(cisempty(&o) != 0){
					if(precedance(*ctop(&o)) == 10)
						cpush(&o, arr[i]);
					else{
						while(precedance(*ctop(&o)) > 10){	
							operation(*ctop(&o));
							c = cpop(&o);
						}
						cpush(&o, arr[i]);
					}
				}
				else
					cpush(&o, arr[i]);
				i++;	
				break;
			case'%':
				if(arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ',' ){
					j = 0;
					Integer I;
					str[k] = '\0';
					I = CreateIntegerFromString(str);
				      //PrintInteger(I);
					push(&p, I);
					state = 0;
				}
				if(cisempty(&o) != 0){
					if(precedance(*ctop(&o)) <= 25)
						cpush(&o, arr[i]);
					else{
						while(precedance(*ctop(&o)) > 25){
							operation(*ctop(&o));
							c = cpop(&o);
						}
						cpush(&o, arr[i]);
					}
				}
				else
					cpush(&o, arr[i]);
				i++;
				break;
			
		
			case'*': 
				if(arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ','){
				      j = 0;
					str[k] = '\0';
					Integer I;
					I = CreateIntegerFromString(str);
					//printf("in*->");
				     // PrintInteger(I);
					push(&p, I);
					state = 0;
				}
				if(cisempty(&o) != 0){
					if(precedance(*ctop(&o)) <= 30)
						cpush(&o, arr[i]);
					else{
						while(precedance(*ctop(&o)) > 30){	
						operation(*ctop(&o));
						c = cpop(&o);	
						}
						cpush(&o, arr[i]);
					}
				}
				else
					cpush(&o, arr[i]);
				i++;	
				break;
				
			case'/': 
				if(arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ','){
					j = 0;
					str[k] = '\0';
					Integer I;
					I = CreateIntegerFromString(str);
				     // PrintInteger(I);
					push(&p, I);
					state = 0;
				}
				if(cisempty(&o) != 0){
					if(precedance(*ctop(&o)) <= 40)
						cpush(&o,arr[i]);
					else{
						while(precedance(*ctop(&o)) > 40){	
						operation(*ctop(&o));
						c = cpop(&o);	
						}
						cpush(&o, arr[i]);
					}
				}
				else
					cpush(&o, arr[i]);
				i++;	
				break;
			
			case'(':
				cpush(&o, arr[i]);
				//printf("%c", arr[i]);
				i++;
				break;
				
			case')':
				if(arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ','){
					j = 0;
					str[k] = '\0';
					Integer I;
					I = CreateIntegerFromString(str);
					//printf("push->");
				      //PrintInteger(I);
					push(&p, I);
					state = 0;
				}
				while(*ctop(&o) != '('){
			        	operation(*ctop(&o));
					c = cpop(&o);	
				}
				c = cpop(&o);
				i++;	
				break;
		
			case ' ':
			 	i++;				
			 	break;
			default:i++;
				printf("Error!\n");
				exit(1);
				break;
		}
	}

	if(arr[i] == '\0' &&arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ',') {
		str[k] = '\0';
		Integer I;
		I = CreateIntegerFromString(str);
		//PrintInteger(I);
		push(&p, I);
		state = 0;
	}
	while(cisempty(&o) != 0){
				operation(*ctop(&o));
				c = cpop(&o);
	}
	return top(&p);
	
}

void operation(char c){
	Integer x,y,z;
	//int a,b;
	x = pop(&p);
	y = pop(&p);
	switch(c){	
		case'+':
			z = AddIntegers( x, y);
			push(&p, z);
			break;
		case'-':
			z = SubstractIntegers(y, x);
			//printf("ans->");
			//PrintInteger(z);
			push(&p, z);
			break;
		/*case '%':
			a = x;
			b = y;
			push(&p, b%a);
			break;*/	
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
		return 25;
	else if( c == '*')
		return 30;
	else if(c == '/')
		return 40;
	else if(c =='(')
		return 0;
}
