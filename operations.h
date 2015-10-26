typedef struct node {
	char *s;
	struct node *next, *prev;
}node;
typedef struct Integer{
	char sign;
	node *head, *tail;
}Integer; 
Integer CreateIntegerFromString(char *str);
Integer AddIntegers(Integer a, Integer b);
Integer SubstractIntegers(Integer a, Integer b);
Integer MultiplyIntegers(Integer a, Integer b); 
Integer DivideIntegers(Integer a, Integer b);
int CompareIntegers(Integer a, Integer b);
void PrintInteger(Integer a);
/*operatons*/
