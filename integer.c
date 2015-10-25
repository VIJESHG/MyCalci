#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "integer.h"
Integer CreateIntegerFromString(char *str) {
	Integer new;
	new.head = new.tail = NULL;
	node *temp;
	int  i = 0, j = 0, k = 0;
	if(str[0] == '-') {
		new.sign = '-';
		strcpy(str, &str[1]);
	}
	else {
		new.sign = '+';
	}
	while(str[i] == '0') {
		i++;
	}
	strcpy(str, &str[i]);
	
	if((strlen(str) % 4) > 0) {
		temp = (node*)malloc(sizeof(node));
		temp->s = (char*)malloc(sizeof(5));
		for(i = 0; i < (strlen(str) % 4); i++) 
			(temp->s)[j++] = str[k++];
		(temp->s)[j] = '\0';
		temp->next = NULL;
		new.head = new.tail = temp; 
	}
	while(str[k] != '\0') {
		temp = (node*)malloc(sizeof(node));
		temp->s = (char*)malloc(5);
		j = 0;
		while(j < 4 && str[k] != '\0')
			(temp->s)[j++] = str[k++];
		(temp->s)[j] = '\0';
		temp->next = NULL;
		if(new.head) {
			new.tail->next = temp;
			temp->prev = new.tail;
		}
		else 
			new.head = temp;
		temp->prev = new.tail;
		new.tail = temp;
	}
	if(!(new.head)) {
		temp = (node*)malloc(sizeof(node));
		temp->s = (char*)malloc(sizeof(2));
		strcpy(temp->s, "0");
		temp->next = NULL;
		new.head = new.tail = temp;
	}
	return new;	
}
Integer AddIntegers(Integer a, Integer b) {
	int n = 0;
	int c = 0;
	int l, i = 0, j, z, f = 0, k, m, zero = 0;
	if(a.sign == b.sign) {
		node *x = a.tail;
		node *y = b.tail;
		while(x || y) {
			n++;
			if(x)
				x = x->prev;
			if(y)
				y = y->prev;
		}
		char result[n * 4 + 2], r[8], fresult[n * 4 + 3], temp[5];
		result[0] = '\0';
		x = a.tail;
		y = b.tail;
		while(x && y) {
			z = (atoi(x->s) + atoi(y->s) + c);
			snprintf(r, 6, "%d", z);
			c = z / 10000;
			if(c == 1) {
				strcpy(r, &r[1]);
					zero = 0;
					while(r[zero] == '0'){
						zero++;
						}
					
			}
			i = 0;
			if(strlen(r) != 4) {
				strcpy(temp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(temp[j] != '\0') 
					r[i++] = temp[j++];
				r[i] = '\0';
			}
			strcat(result, r);
			x = x->prev;
			y = y->prev; 
		} 	
		while(x) {
			z = atoi(x->s) + c;
			snprintf(r, 6, "%d", z);
			c = z / 10000;
			if(c == 1) {
				strcpy(r, &r[1]);
				zero = 0;
				while(r[zero] == '0')
					zero++;
				
			}
			i = 0;
			if(strlen(r) != 4) {
				strcpy(temp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(temp[j] != '\0') 
					r[i++] = temp[j++];
				r[i] = '\0';
			}
			strcat(result, r);
			x = x->prev;
		}
		while(y) {
			z = atoi(y->s) + c;
			snprintf(r, 6, "%d", z);
			c = z / 10000;
			if(c == 1) {
				strcpy(r, &r[1]);
				zero = 0;
				while(r[zero] == '0')
					zero++;
			}
			i = 0; 
			if(strlen(r) != 4) {
				strcpy(temp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(temp[j] != '\0') 
					r[i++] = temp[j++];
				r[i] = '\0';
			}
			strcat(result, r); 
			y = y->prev;
		}
		l = strlen(result);
		k = 0;
		if((a.sign == '-') && (c == 0)) 
			fresult[k++] = '-';
		j = l;
		m = l % 4;
		j = l - m;
		for(i = 0; i < m; i++) {
			fresult[k++] = result[j++];
			l--;
		}
		while(l > 0) {
			j = l - 4;
			for(i = 0; i < 4; i++) {
				fresult[k++] = result[j++];
				l--;
			}
		}
		fresult[k] = '\0';
		i = 0;
		while(fresult[i] == '0' && i < 4)
		  		i++;
		strcpy(fresult, &fresult[i]);
		i = 0;
		if(zero != 0) {
			strcpy(result, fresult);
			if(zero == 1) 
				strcpy(fresult, "0");
			else if(zero == 2)
				strcpy(fresult, "00");
			else if(zero == 3)
				strcpy(fresult, "000");
			else if(zero == 4)
				strcpy(fresult, "0000");
			strcat(fresult, result);
		}
		j = 0;
		if(c == 1){
			strcpy(result, fresult);
			if(a.sign == '-')
				strcpy(fresult, "-1"); 
			else
				strcpy(fresult, "1");
			strcat(fresult, result);
		}
		return CreateIntegerFromString(fresult);
	}
	else {
		if(a.sign == '-')
			b.sign = '-';
		else 
			b.sign = '+'; 
		return SubstractIntegers(a, b);
	}
}
Integer SubstractIntegers(Integer a, Integer b) {
	Integer big, small;
	int n = 0, c = 0, state = 0, z, j, l, i, m, k;
	char str[2], temp[5];
	node *x, *y;
	x = a.head;
	y = b.head;
	while(x && y) {
		n++;
		if(x)
			x = x->next;
		if(y)	
			y = y->next;
	}
	if(x) 
		big = a;
	else if(y) 
		big = b;
	else {
		x = a.head;
		y = b.head;
		while(((atoi(x->s) - atoi(y->s)) == 0) && (x->next)) {
			x = x->next;
			y = y->next; 
		}
		if((atoi(x->s) - atoi(y->s)) >= 0) 
			big = a;
		else 
			big = b;
	}
	if(big.head == a.head)
		small = b;
	else
		small = a;
	if(big.sign == small.sign) {
		node *x = big.tail;
		node *y = small.tail;
		while(x || y) {
			n++;
			if(x)
				x = x->prev;
			if(y)
				y = y->prev;
		}
		char result[n * 4 + 2], r[6], fresult[n * 4 + 3];
		result[0] = '\0';
		x = big.tail;
		y = small.tail;
		while(x && y) {
			if(atoi(x->s) >= atoi(y->s)) {
				state = 0;
				z = (atoi(x->s) - atoi(y->s) - c);
			}
			else {
				state = 1;
				z = ((pow(10,(strlen(x->s))) + atoi(x->s)) - atoi(y->s) - c);
			}
			snprintf(r, 6, "%d", z);
			if(state == 1)
				c = 1;
			else 
				c = 0;
			i = 0;
			if(strlen(r) != 4) {
				strcpy(temp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(temp[j] != '\0') 
					r[i++] = temp[j++];
				r[i] = '\0';
			}
			strcat(result, r);
			x = x->prev;
			y = y->prev;
		} 
		while(x) {
			if(atoi(x->s) >= c) {
				state = 0;
				z = (atoi(x->s) - c);
			}
			else {
				state = 1;
				z = ((pow(10,(strlen(x->s))) + atoi(x->s)) - c);
			}
			snprintf(r, 6, "%d", z);
			if(state == 1)
				c = 1;
			else 
				c = 0;
			i = 0;
			if(strlen(r) != 4) {
				strcpy(temp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(temp[j] != '\0') 
					r[i++] = temp[j++];
				r[i] = '\0';
			}
			strcat(result, r);
			x = x->prev;
		}		
		while(y) {
			if(atoi(y->s) >= c) {
				state = 0;
				z = (atoi(y->s) - c);
			}
			else {
				state = 1;
				z = ((pow(10,(strlen(y->s))) + atoi(y->s)) - c);
			}
			snprintf(r, 6, "%d", z);
			if(state == 1)
				c = 1;
			else 
				c = 0;
			i = 0;
			if(strlen(r) != 4) {
				strcpy(temp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(temp[j] != '\0') 
					r[i++] = temp[j++];
				r[i] = '\0';
			}
			strcat(result, r);
			y = y->prev;
		}
		l = strlen(result);
		while(result[l - 1] == 0) 
			l--;
		result[l] = '\0';	
		k = 0;
		if((big.head == b.head) && (b.sign == '+')) 
			fresult[k++] = '-';
		else if((big.head == a.head) && (a.sign == '-')) 
			fresult[k++] = '-';
		j = l;
		m = l % 4;
		j = l - m;
		for(i = 0; i < m; i++) {
			fresult[k++] = result[j++];
			l--;
		}
		while(l > 0) {
			j = l - 4;
			for(i = 0; i < 4; i++) {
				fresult[k++] = result[j++];
				l--;
			}
		}
		fresult[k] = '\0';
		return CreateIntegerFromString(fresult);
	}
	else {
		
		if(a.sign == '-')
			b.sign = '-';
		else 
			b.sign = '+'; 
		return AddIntegers(a, b);	
	}
}
Integer MultiplyIntegers(Integer a, Integer b) {
	int n = 0, zc = 0, z, c = 0, i, j,f;
	Integer sum;
	char str[2];
	strcpy(str, "0");
	sum = CreateIntegerFromString(str);
	node *x = a.tail;
	node *y = b.tail;
	while(x || y) {
		n++;
		if(x)
			x = x->prev;
		if(y)
			y = y->prev;
	}
	char result[n * 8 + 1], r[9], fresult[n * 8 + 1], temp[9];
	
	result[0] = '\0';
	y = b.tail;
	while(y) {
		c = 0;
		fresult[0] = '\0';
		x = a.tail;
		while(x) {
			r[0] = '\0';
			strcpy(result, fresult);
			z = (atoi(y->s) * atoi(x->s) + c);
			snprintf(r, 9, "%d", z);
			f = z / 10000;
			if( f >= 1 ) {
				if(strlen(x->s) >= strlen(y->s)) {
					strcpy(temp, &r[strlen(r) - strlen(x->s)]);
					r[strlen(r) - strlen(x->s)] = '\0';
					c = atoi(r);
				}
				else if (strlen(y->s) > strlen(x->s)) {
					strcpy(temp, &r[strlen(r) - strlen(y->s)]);
					r[strlen(r) - strlen(y->s)] = '\0';
					c = atoi(r);
				}
			}
			
			else {
				strcpy(temp, r);
				c = 0;
			}	
			i = 0;
			if(strlen(temp) == strlen(r)) {
				strcpy(r, temp);
				j = 4 - strlen(temp);
				while(j > 0) {
					temp[i++] = '0';
					j--;	
				}
				while(r[j] != '\0') 
					temp[i++] = r[j++];
				temp[i] = '\0';
			}
			strcpy(fresult, temp);
			strcat(fresult, result);
			x = x->prev;
		}
		for(i = 0; i < (4 * zc); i++) 
			strcat(fresult, "0");
		zc++;
		if(c > 0) {
			strcpy(result, fresult);
			snprintf(fresult, 5, "%d", c);
			strcat(fresult, result);
		}
		sum = AddIntegers(CreateIntegerFromString(fresult), sum);
		y = y->prev;
	}
	if(a.sign == b.sign)
		sum.sign = '+';
	else
		sum.sign = '-';
	return sum;
}
/*int CompareIntegers(Integer a, Integer b) {
	Integer big, small;
	int n = 1;
	node *x, *y;
	x = a.head;
	y = b.head;
	while(x && y) {
		//n++;
		if(x)
			x = x->next;
		if(y)	
			y = y->next;
	}
	if(x) {
		big = a;
		return -n;
	}
	else if(y){
		big = b;
		return n;
	}
	else {
		x = a.head;
		y = b.head;
		while(((atoi(x->s) - atoi(y->s)) == 0) && (x->next)) {
			x = x->next;
			y = y->next; 
		}
		if((atoi(x->s) - atoi(y->s)) >= 0) {
			big = a;
			return -n;
			}
		else {
			big = b;
			return n;
		}
	}
	if(big.head == a.head) {
		small = b;
		return -n;
	}
	else {
		small = a;
		return n;
	}
}

Integer DivideIntegers(Integer a, Integer b) {
	char str[128];
	int count = 0;
	int c = -1;
	Integer d = b;
	while(c < 0) {
		c = CompareIntegers(a,b);
		b = AddIntegers(b,d);
		count++;
	}
		snprintf(str,128,"%d",count-1);	
	return CreateIntegerFromString(str);
}	
*/
int CompareIntegers(Integer a, Integer b) {
	int n = 0, m = 0, i,j, d = 100, c;
	node *x, *y;
	x = a.head;
	y = b.head;
	while(x || y) {
		if(x) {
			for(i = 0; i < strlen(x->s);i++) {
				n++;
			}
			x = x->next;
		}
		else {
			for(j = 0; j < strlen(y->s);j++) {
				m++;
			}
			y = y->next;
		}
	}
	if((n - m) != 0) {
		return (n - m);
	}
	if( (n - m) == 0) {
		x = a.head;
	      y = b.head;
		while(x || y) {
				for(i = 0; i < n; i++) {
					c = strcmp(x->s, y->s);
					if(c > 0) {
						return d;  	
					}
					if(c < 0) {
						return -d;
					}
					if(c = 0) {
						return 0;
					}
				}
				x = x->next;
				y = y->next;
		}
	}
}
Integer DivideIntegers(Integer a, Integer b) {
	char str1[128];
	char str2[128];
	int count = 0, state;
	int c = 0;
	long f;
	Integer d = b;
	Integer m;
	c = CompareIntegers(a,b);
	if(c == 0) {
		snprintf(str1,128,"%d",c);	
	return CreateIntegerFromString(str1);
	}	
	if(c > 0) {
		f = pow(10,c); 
		snprintf(str2,128,"%ld",f);
		m = CreateIntegerFromString(str2);
		b = MultiplyIntegers(b, m);
		printf("\n");
		PrintInteger(b);
		c = 0;
		c = CompareIntegers(a,b);
		if(c > 0) { 
		while(c > 0) {
			state = 0;
			b = AddIntegers(b,d);	
			c = 0;
			c = CompareIntegers(a,b);
			count++;
		}
		}
		else {
			state = 1;
			while(c < 0) {
			b = SubstractIntegers(b,d);	
			c = 0;
			c = CompareIntegers(a,b);
			count++;
		}	 
	}
}
		if(state == 0){
		snprintf(str1,128,"%ld",(f + count-1));	
	return CreateIntegerFromString(str1);
		}
		if(state == 1) {
			snprintf(str1,128,"%ld",(f - count));	
	return CreateIntegerFromString(str1);
		}
		
}

void PrintInteger(Integer a) {
		int i, state = 0;	
		node *x;
		x = a.head; 
		while(x) {
			i = 0;
			while((x->s)[i] != '\0') {
				if((x->s)[i] != '0') {
					state = 1;
					break;
				}
				i++;
			}
			if(state == 1)
				break;
			x = x->next;
		}
		x = a.head;
		if(state == 1) {
			if(a.sign == '-')
				printf("-");
			while(x) {
				printf("%s", x->s);
				x = x->next;
			}
			printf("\n");
		}
		else 
			printf("0\n");
}
