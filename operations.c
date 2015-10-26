#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "operations.h"
Integer CreateIntegerFromString(char *str) {
	Integer new;
	new.head = new.tail = NULL;
	node *tmp;
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
		tmp = (node*)malloc(sizeof(node));
		tmp->s = (char*)malloc(sizeof(5));
		for(i = 0; i < (strlen(str) % 4); i++) 
			(tmp->s)[i] = str[k++];
		(tmp->s)[i] = '\0';
		tmp->next = NULL;
		new.head = new.tail = tmp; 
	}
	while(str[k] != '\0') {
		tmp = (node*)malloc(sizeof(node));
		tmp->s = (char*)malloc(5);
		j = 0;
		while(j < 4 && str[k] != '\0')
			(tmp->s)[j++] = str[k++];
		(tmp->s)[j] = '\0';
		tmp->next = NULL;
		if(new.head) {
			new.tail->next = tmp;
			tmp->prev = new.tail;
		}
		else 
			new.head = tmp;
		tmp->prev = new.tail;
		new.tail = tmp;
	}
	if(!(new.head)) {
		tmp = (node*)malloc(sizeof(node));
		tmp->s = (char*)malloc(sizeof(2));
		strcpy(tmp->s, "0");
		tmp->next = NULL;
		new.head = new.tail = tmp;
	}
	return new;	
}
Integer AddIntegers(Integer a, Integer b) {
	int n = 0;
	int carry = 0;
	int l, i = 0, j, t, k, m, zero = 0;
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
		char ians[n * 4 + 2], r[8], ans[n * 4 + 3], tmp[5];
		
		x = a.tail;
		y = b.tail;
		ians[0] = '\0';
		while(x && y) {
			t = (atoi(x->s) + atoi(y->s) + carry);
			snprintf(r, 6, "%d", t);
			carry = t / 10000;
			if(carry == 1) {
				strcpy(r, &r[1]);
					zero = 0;
					while(r[zero] == '0'){
						zero++;
						}
					
			}
			i = 0;
			if(strlen(r) != 4) {
				strcpy(tmp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(tmp[j] != '\0') 
					r[i++] = tmp[j++];
				r[i] = '\0';
			}
			strcat(ians, r);
			x = x->prev;
			y = y->prev; 
		} 	
		while(x) {
			t = atoi(x->s) + carry;
			snprintf(r, 6, "%d", t);
			carry = t / 10000;
			if(carry == 1) {
				strcpy(r, &r[1]);
				zero = 0;
				while(r[zero] == '0')
					zero++;
				
			}
			i = 0;
			if(strlen(r) != 4) {
				strcpy(tmp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(tmp[j] != '\0') 
					r[i++] = tmp[j++];
				r[i] = '\0';
			}
			strcat(ians, r);
			x = x->prev;
		}
		while(y) {
			t = atoi(y->s) + carry;
			snprintf(r, 6, "%d", t);
			carry = t / 10000;
			if(carry == 1) {
				strcpy(r, &r[1]);
				zero = 0;
				while(r[zero] == '0')
					zero++;
			}
			i = 0; 
			if(strlen(r) != 4) {
				strcpy(tmp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(tmp[j] != '\0') 
					r[i++] = tmp[j++];
				r[i] = '\0';
			}
			strcat(ians, r); 
			y = y->prev;
		}
		l = strlen(ians);
		k = 0;
		if((a.sign == '-') && (carry == 0)) 
			ans[k++] = '-';
		j = l;
		m = l % 4;
		j = l - m;
		for(i = 0; i < m; i++) {
			ans[k++] = ians[j++];
			l--;
		}
		while(l > 0) {
			j = l - 4;
			for(i = 0; i < 4; i++) {
				ans[k++] = ians[j++];
				l--;
			}
		}
		ans[k] = '\0';
		i = 0;
		while(ans[i] == '0' && i < 4)
		  		i++;
		strcpy(ans, &ans[i]);
		i = 0;
		if(zero != 0) {
			strcpy(ians, ans);
			if(zero == 1) 
				strcpy(ans, "0");
			else if(zero == 2)
				strcpy(ans, "00");
			else if(zero == 3)
				strcpy(ans, "000");
			else if(zero == 4)
				strcpy(ans, "0000");
			strcat(ans, ians);
		}
		j = 0;
		if(carry == 1){
			strcpy(ians, ans);
			if(a.sign == '-')
				strcpy(ans, "-1"); 
			else
				strcpy(ans, "1");
			strcat(ans, ians);
		}
		return CreateIntegerFromString(ans);
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
	Integer isbigger, issmaller;
	int n = 0, borrow = 0, state = 0, t, j, l, i, m, k;
	char str[2], tmp[5];
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
		isbigger = a;
	else if(y) 
		isbigger = b;
	else {
		x = a.head;
		y = b.head;
		while(((atoi(x->s) - atoi(y->s)) == 0) && (y->next)) {
			x = x->next;
			y = y->next; 
		}
		if((atoi(x->s) - atoi(y->s)) >= 0) 
			isbigger = a;
		else 
			isbigger = b;
	}
	if(isbigger.head == a.head)
		issmaller = b;
	else
		issmaller = a;
	if(isbigger.sign == issmaller.sign) {
		node *x = isbigger.tail;
		node *y = issmaller.tail;
		while(x || y) {
			n++;
			if(x)
				x = x->prev;
			if(y)
				y = y->prev;
		}
		char ians[n * 4 + 2], r[6], ans[n * 4 + 3];
		ians[0] = '\0';
		x = isbigger.tail;
		y = issmaller.tail;
		while(x && y) {
			if(atoi(x->s) >= atoi(y->s)) {
				state = 0;
				t = (atoi(x->s) - atoi(y->s) - borrow);
			}
			else {
				state = 1;
				t = ((pow(10,(strlen(x->s))) + atoi(x->s)) - atoi(y->s) - borrow);
			}
			snprintf(r, 6, "%d", t);
			if(state == 1)
				borrow = 1;
			else 
				borrow = 0;
			i = 0;
			if(strlen(r) != 4) {
				strcpy(tmp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(tmp[j] != '\0') 
					r[i++] = tmp[j++];
				r[i] = '\0';
			}
			strcat(ians, r);
			x = x->prev;
			y = y->prev;
		} 
		while(x) {
			if(atoi(x->s) >= borrow) {
				state = 0;
				t = (atoi(x->s) - borrow);
			}
			else {
				state = 1;
				t = ((pow(10,(strlen(x->s))) + atoi(x->s)) - borrow);
			}
			snprintf(r, 6, "%d", t);
			if(state == 1)
				borrow = 1;
			else 
				borrow = 0;
			i = 0;
			if(strlen(r) != 4) {
				strcpy(tmp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(tmp[j] != '\0') 
					r[i++] = tmp[j++];
				r[i] = '\0';
			}
			strcat(ians, r);
			x = x->prev;
		}		
		while(y) {
			if(atoi(y->s) >= borrow) {
				state = 0;
				t = (atoi(y->s) - borrow);
			}
			else {
				state = 1;
				t = ((pow(10,(strlen(y->s))) + atoi(y->s)) - borrow);
			}
			snprintf(r, 6, "%d", t);
			if(state == 1)
				borrow = 1;
			else 
				borrow = 0;
			i = 0;
			if(strlen(r) != 4) {
				strcpy(tmp, r);
				j = 4 - strlen(r);
				while(j > 0) {
					r[i++] = '0';
					j--;	
				}
				while(tmp[j] != '\0') 
					r[i++] = tmp[j++];
				r[i] = '\0';
			}
			strcat(ians, r);
			y = y->prev;
		}
		l = strlen(ians);
		while(ians[l - 1] == 0) 
			l--;
		ians[l] = '\0';	
		k = 0;
		if((isbigger.head == b.head) && (b.sign == '+')) 
			ans[k++] = '-';
		else if((isbigger.head == a.head) && (a.sign == '-')) 
			ans[k++] = '-';
		j = l;
		m = l % 4;
		j = l - m;
		for(i = 0; i < m; i++) {
			ans[k++] = ians[j++];
			l--;
		}
		while(l > 0) {
			j = l - 4;
			for(i = 0; i < 4; i++) {
				ans[k++] = ians[j++];
				l--;
			}
		}
		ans[k] = '\0';
		return CreateIntegerFromString(ans);
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
	int n = 0, zero = 0, t, carry = 0, i, j,f;
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
	char ians[n * 8 + 1], r[9], ans[n * 8 + 1], tmp[9];
	
	ians[0] = '\0';
	y = b.tail;
	while(y) {
		carry = 0;
		ans[0] = '\0';
		x = a.tail;
		while(x) {
			r[0] = '\0';
			strcpy(ians, ans);
			t = (atoi(y->s) * atoi(x->s) + carry);
			snprintf(r, 9, "%d", t);
			f = t / 10000;
			if( f >= 1 ) {
				if(strlen(x->s) >= strlen(y->s)) {
					strcpy(tmp, &r[strlen(r) - strlen(x->s)]);
					r[strlen(r) - strlen(x->s)] = '\0';
					carry = atoi(r);
				}
				else if (strlen(y->s) > strlen(x->s)) {
					strcpy(tmp, &r[strlen(r) - strlen(y->s)]);
					r[strlen(r) - strlen(y->s)] = '\0';
					carry = atoi(r);
				}
			}
			
			else {
				strcpy(tmp, r);
				carry = 0;
			}	
			i = 0;
			if(strlen(tmp) == strlen(r)) {
				strcpy(r, tmp);
				j = 4 - strlen(tmp);
				while(j > 0) {
					tmp[i++] = '0';
					j--;	
				}
				while(r[j] != '\0') 
					tmp[i++] = r[j++];
				tmp[i] = '\0';
			}
			strcpy(ans, tmp);
			strcat(ans, ians);
			x = x->prev;
		}
		for(i = 0; i < (4 * zero); i++) 
			strcat(ans, "0");
		zero++;
		if(carry > 0) {
			strcpy(ians, ans);
			snprintf(ans, 5, "%d", carry);
			strcat(ans, ians);
		}
		sum = AddIntegers(CreateIntegerFromString(ans), sum);
		y = y->prev;
	}
	if(a.sign == b.sign)
		sum.sign = '+';
	else
		sum.sign = '-';
	return sum;
}
int CompareIntegers(Integer a, Integer b) {
	int n = 0, m = 0, i,j, d = 1000, cmp;
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
					cmp = strcmp(x->s, y->s);
					if(cmp > 0) {
						return d;  	
					}
					if(cmp < 0) {
						return -d;
					}
					if(cmp = 0) {
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
	long f = 1;
	Integer d = b;
	Integer m;
	c = CompareIntegers(a,b);
	//printf("%d	",c);
	if(c == 0) {
		snprintf(str1,128,"%d",c);	
		return CreateIntegerFromString(str1);
	}
	if((c == 1000) || (c == -1000)) {
		if(c == 1000) {
			while(c >= 0) {
				state = 0;
			b = AddIntegers(b,d);
			PrintInteger(b);	
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
	if((c > 0) && (c < 1000)) {
		f = pow(10,c); 
		snprintf(str2,128,"%ld",f);
		m = CreateIntegerFromString(str2);
		b = MultiplyIntegers(b, m);
		printf("\n");
		PrintInteger(b);
		c = 0;
		c = CompareIntegers(a,b);
		if(c > 0) { 
		while(c >= 0) {
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
