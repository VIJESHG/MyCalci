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
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "operations.h"
Integer inInt(Integer a,char digit) {        		/* initialization of integer */
	char str[4];
	snprintf(str,4,"%c",digit);
		a = CreateIntegerFromString(str);
		return a;
}
Integer CreateIntegerFromString(char *str) {
	Integer myint;
	myint.head = myint.tail = NULL;
	node *temp;
	int  i = 0, j = 0, k = 0;
	if(str[0] == '-') {
		myint.sign = '-';               		/* store sign */
		strcpy(str, &str[1]);           		/* copy the string after sign */
	}
	else
		myint.sign = '+';
		
	while(str[i] == '0') 
		i++;
		
	strcpy(str, &str[i]);
	
	if((strlen(str) % 4) > 0) {                 	/* create node of remaining srting */
		temp = (node*)malloc(sizeof(node));
		temp->s = (char*)malloc(sizeof(5));
		
		for(i = 0; i < (strlen(str) % 4); i++) 
			(temp->s)[j++] = str[k++];
			
		(temp->s)[j] = '\0';
		temp->next = NULL;
		myint.head = myint.tail = temp; 
	}
	while(str[k] != '\0') {                    	/* create node for every four char */ 
		temp = (node*)malloc(sizeof(node));
		temp->s = (char*)malloc(5);
		j = 0;
		while(j < 4 && str[k] != '\0')
			(temp->s)[j++] = str[k++];
			
		(temp->s)[j] = '\0';
		temp->next = NULL;
		if(myint.head) {                 		/* second onward nodes */
			myint.tail->next = temp;
			temp->prev = myint.tail;
		}
		else 
			myint.head = temp;   			/* first node */
			
		temp->prev = myint.tail;
		myint.tail = temp;
	}
	if(!(myint.head)) {                       	/* for zero */
		temp = (node*)malloc(sizeof(node));
		temp->s = (char*)malloc(sizeof(2));
		strcpy(temp->s, "0");
		temp->next = NULL;
		myint.head = myint.tail = temp;
	}
	return myint;	                    		/* return created integer */
}
Integer AddIntegers(Integer a, Integer b) {
	int n = 0;
	int c = 0;
	int l, i = 0, j, z, f = 0, k, m, zero = 0;
	if(a.sign == b.sign) {
		node *x = a.tail;
		node *y = b.tail;
		while(x || y) {        				/* find number of nodes in larger integer */
			n++;
			if(x)
				x = x->prev;
			if(y)
				y = y->prev;
		}
		char result[n * 4 + 2], r[6], fresult[n * 4 + 3], temp[5];
		result[0] = '\0';
		x = a.tail;
		y = b.tail;
		while(x && y) {
			z = (atoi(x->s) + atoi(y->s) + c);  /* addition of nodes from left */
			snprintf(r, 6, "%d", z);
			c = z / 10000;                      /* carry */
			if(c == 1) {
				strcpy(r, &r[1]);             /* cp number after carry digit */
					zero = 0;
					while(r[zero] == '0'){ 	/* count for trailing zeroes */
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
			strcat(result, r);    			/*result*/
			x = x->prev;	
			y = y->prev; 
		} 	
		while(x) {                    		/* x is not over but y over */
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
		while(y) {                      		/* x over but y not over */
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
		if(zero != 0) {                    			/* if number after addition is 0, 1,2,3 digit */
			strcpy(result, fresult);     			/* add zero after it to make 4 digit */
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
		if(c == 1){                             		/* return answer with sign */
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
	while(x && y) {              					/* find the length of larger number */
		n++;
		if(x)
			x = x->next;
		if(y)	
			y = y->next;
	}
	if(x)                         				/* determine bigger one */
		big = a;
	else if(y) 
		big = b;
	else {
		x = a.head;            					/* if are of same length */
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
		while(x || y) {          				/* max lenght required */
			n++;		
			if(x)
				x = x->prev;
			if(y)
				y = y->prev;
		}
		char result[n * 4 + 2], r[6], fresult[n * 4 + 3];
		result[0] = '\0';
		x = big.tail;                     			/* start from left */
		y = small.tail;
		while(x && y) {
			if(atoi(x->s) >= atoi(y->s)) {           	/* if first is bigger */
				state = 0;
				z = (atoi(x->s) - atoi(y->s) - c);
			}
			else {                                  	/* if second is bigger */
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
			strcat(result, r);    					/* add to result */
			x = x->prev;
			y = y->prev;
		} 
		while(x) {                  					/* second over */   
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
		while(y) {                          			/* first over */
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
		while(result[l - 1] == 0)       				/* trailing zeros */
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
		return CreateIntegerFromString(fresult);        	/* return answer */
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
	sum = CreateIntegerFromString(str);              		/* initialize sum = 0*/
	node *x = a.tail;
	node *y = b.tail;
	while(x || y) {   							/* find max length required */
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
			z = (atoi(y->s) * atoi(x->s) + c);    		/* multiply nodes */
			snprintf(r, 9, "%d", z);
			f = z / 10000;                        		/* carry */
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
int CompareIntegers(Integer a, Integer b) {
	int n = 0, m = 0, i,j, d = 1000, c;
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
Integer AddDigitToInteger(Integer a, char digit) {
	int n = 0, i = 0, j;
	node *x;
	x = a.head; 
	while(x) {
		x = x->next;
		n++;
	}
	char str[(n + 1) * 4];
	if(a.sign == '-')
		str[i++] = '-';
	x = a.head; 
	while(x) {
		j = 0;
		while((x->s)[j] != '\0') 
			str[i++] = (x->s)[j++];
		x = x->next;
	}
	str[i++] = digit;
	str[i] = '\0';
	return CreateIntegerFromString(str); 
}
Integer DivideIntegers(Integer a, Integer b) {
	char str[128];
	int  state,c = 0,i;
	Integer count = inInt(count,'0');
	Integer f = inInt(f,'1');
	Integer g = inInt(g, '1');
	Integer h = inInt(h,'1');
	Integer d = b;
	Integer m = inInt(m,'1');;
	c = CompareIntegers(a,b);
	if(c == 0) {	
		return g;
	}
	if((c == 1000) || (c == -1000)) {
		if(c == 1000) {
			while(c >= 0) {
				state = 0;
			b = AddIntegers(b,d);
			//PrintInteger(b);	
			c = 0;
			c = CompareIntegers(a,b);
			count = AddIntegers(count,g);
			//PrintInteger(count);
			}
		}
		else {
			d = inInt(d,'0');	
		return d;
			}
	}	
	if((c > 0) && (c < 1000)) { 
		snprintf(str,128,"%d",c);
		for(i = 0; i < c; i++){
			m = AddDigitToInteger(m,'0');
		}
		//PrintInteger(m);
		b = MultiplyIntegers(b, m);
		printf("\n");
		//PrintInteger(b);
		c = 0;
		c = CompareIntegers(a,b);
		if(c > 0) { 
		while(c >= 0) {
			state = 0;
			b = AddIntegers(b,d);
			//PrintInteger(b);	
			c = 0;
			c = CompareIntegers(a,b);
			count = AddIntegers(count,g);
			//PrintInteger(count);
		}
		}
		else {
			state = 1;
			while(c < 0) {
			b = SubstractIntegers(b,d);	
			c = 0;
			c = CompareIntegers(a,b);
			count = AddIntegers(count,g);
		}	 
	}
}
	if(state == 0){
		return AddIntegers(m,SubstractIntegers(count,g));
		}
		if(state == 1) {
			return SubstractIntegers(m,count);
		}
}
Integer ModIntegers(Integer a, Integer b) {
	Integer I;
	char str[128];
	int  state = 0,c = 0,i;
	Integer g = inInt(g, '0');
	Integer d = b;
	Integer m = inInt(m,'1');
	c = CompareIntegers(a,b);
	if(c == 0) {	
		return g;
	}
	if((c == 1000) || (c == -1000)) {
		if(c == 1000) {
			while(c >= 0) {
				I = b;
				b = AddIntegers(b,d);	
				c = 0;
				c = CompareIntegers(a,b);
			}
			return SubstractIntegers(a,I);
		}
		else {
			return a;
		}
	}
	if((c > 0) && (c < 1000)) { 
		state = 1;
		snprintf(str,128,"%d",c);
		for(i = 0; i < c; i++){
			m = AddDigitToInteger(m,'0');
		}
		I = b;
		b = MultiplyIntegers(b, m);
		c = 0;
		c = CompareIntegers(a,b);
		if(c > 0) { 
		while(c >= 0) {
			I = b;
			b = AddIntegers(b,d);
			c = 0;
			c = CompareIntegers(a,b);
		}
		}
		else {
			
			while(c < 0) {
			
			b = SubstractIntegers(b,d);
			I = b;	
			c = 0;
			c = CompareIntegers(a,b);
		}	 
	}
}
	if(state == 1) {
		return SubstractIntegers(a,I);
	}
}
void DecToHex(Integer DeciNum) {
	
	Integer zero = inInt(zero,'0');
	Integer remainder, quotient,temp;
	Integer cs1 = inInt(cs1,'1');
	Integer cs2 = inInt(cs2,'1');
	Integer cs3 = inInt(cs3,'4');
	Integer cs4 = inInt(cs4,'5');
	cs1 = AddDigitToInteger(cs1,'6');
	cs2 = AddDigitToInteger(cs2,'0');
	cs3 = AddDigitToInteger(cs3,'8');
	cs4 = AddDigitToInteger(cs4,'5');
	
	int i = 1,j,c,d;
    	char HexNum[100];
	quotient = DeciNum;
	//PrintInteger(quotient);
	c = CompareIntegers(quotient,zero);
	printf("%d	",c);
    	while(c != 0){
        	temp = ModIntegers(quotient,cs1);
        	//PrintInteger(temp);
        d = CompareIntegers(cs2,temp);
        printf("%d",d);	
      if(d > 0) {
           temp = AddIntegers(temp,cs3);
           PrintInteger(temp);
       }
      else
         temp = AddIntegers(temp,cs4);
      node *x;
	x = temp.head;
      HexNum[i++] = atoi(x->s);
      quotient = DivideIntegers(quotient, cs1);
      c = CompareIntegers(quotient,zero);
  }

    for(j = i - 1; j > 0; j--)
    	printf("%c",HexNum[j]);
    printf("\n");  
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
				//printf("	%d ",atoi(x->s));
				x = x->next;
			}
			printf("\n");
		}
		else 
			printf("0\n");
}
