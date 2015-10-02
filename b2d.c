#include <math.h>
#include <string.h>
void binaryToDecimal(char *binary, int *decimal, int *len) {
static int num, i = 0;
if (*len > 0) {
*len = *len - 1;
num = *(binary + *len) - '0';
*decimal = *decimal + (num * pow(2, i++));
binaryToDecimal(binary, decimal, len);
}
return;
}
