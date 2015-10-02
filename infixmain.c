#include <stdio.h>
int infix(char *arr);
int main(){
	double ans;
	char arr[128];
	scanf("%[^\n]", arr);
	ans = infix(arr);
	printf("Answer: %lf\n", ans);
	return 0;
}
