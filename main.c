#include <stdio.h>
#include "integer.h"
Integer infix(char *arr);
int main(){
	Integer ans;
	char arr[128];
	scanf("%[^\n]", arr);
	ans = infix(arr);
	printf("Answer: ");
	PrintInteger(ans);
	return 0;
}
