#include <stdio.h>
#include <string.h>
void binaryToDecimal(char *binary, int *decimal, int *len);
int main() {
char binary[256];
int decimal = 0, len;
printf("Enter your binary input:");
fgets(binary, 256, stdin);
binary[strlen(binary) - 1]= '\0';
len = strlen(binary);
binaryToDecimal(binary, &decimal, &len);
printf("Decimal Value: %d\n", decimal);
return 0;
}
