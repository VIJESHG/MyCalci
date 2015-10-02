#include <stdio.h>
#include "stack.h"
stack p;
cstack o;
int precedance(char c);
void operation(char c);
int infix(char *arr){
	int i = 0, sum = 0;
	char c;
	init(&p);
	cinit(&o);
	while(arr[i] != '\0'){
		switch(arr[i]){
			case '1': case'2': case '3': case '4':
			case '5': case'6': case '7': case '8':
			case '9': case'0': 
				sum = sum * 10 + arr[i] -'0';
				i++;
				break;

			case'+':
				if(arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ',' ){
					push(&p, sum);
					sum = 0;
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
					push(&p, sum);
					sum = 0;
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
					push(&p, sum);
					sum = 0;
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
					push(&p, sum);
					sum = 0;
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
					push(&p, sum);
					sum = 0;
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
				i++;
				break;
				
			case')':
				if(arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ','){
					push(&p, sum);
					sum = 0;
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

	if(arr[i] == '\0' &&arr[i-1] != ')' && arr[i-1] != ' ' && arr[i-1] != ',')
		push(&p, sum);
	while(cisempty(&o) != 0){
				operation(*ctop(&o));
				c = cpop(&o);
	}
	return top(&p);
	
}

void operation(char c){
	double x,y;
	int a,b;
	x = pop(&p);
	y = pop(&p);
	switch(c){	
		case'+':
			push(&p, x+y);
			break;
		case'-':
			push(&p, y-x);
			break;
		case '%':
			a = x;
			b = y;
			push(&p, b%a);
			break;	
		case'*':
			push(&p, y*x);
			break;
		case'/':
			push(&p, y/x);
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
