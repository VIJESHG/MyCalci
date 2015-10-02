
#include <math.h>
double power(double, int);
double fact(int x);
double power(double x, int n){
	int i = 1;
	double val, result = 1;    
        while (i <= n) 
       {
               
                val = pow((double)x, (double)i)/fact(i);
                result = result + val;
                i = i + 1;
        }
        
        return result;
  }
double fact(int x) {
        double result = 1.0;
        while (x > 0) {
                result = result * x;
                x--;
        }
        return (result);
  }
