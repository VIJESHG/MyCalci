#include <stdio.h>
#include <math.h>
double power(long long x, long long y) {
	double power = 1, term = x;
	int sign = (y > 0 ? 1 : -1);
	if(sign == -1) { 
		y = -y;
	}
	if(x == 0 && y == 0) {
		return NAN;
	}
	while(y > 0) {
		if( (y % 3) == 1) {
			power *= term;
		}
		else if((y % 3) == 2) {
			power *= term * term;
		}
		term = term * term * term;
		y = (y / 3);
	}
	if(sign == -1)
	return power = (double) (1.0/(power));
	return (double)power;
}
int main() {
	long long i, j;
	printf("Enter the values of x and y:\n");
	scanf("%lli%lli", &i, &j);
	printf("x to the power y is:\n");
	printf("%lf\n", power(i, j));
	return 0;
}
			
			
