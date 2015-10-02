#include <stdio.h>
#include <math.h>
double power(double, int);
int main() {
        double x, result;
        int n, i = 1;
        printf("Enter the value for x:");
        scanf("%lf", &x);
        printf("Enter the value for n:");
        scanf("%d", &n); 
        result = power(x, n);
        printf("%lf\n", result);    
        return 0;
}
