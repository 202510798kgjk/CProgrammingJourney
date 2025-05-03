#include <stdio.h>

int main() {
	int a = 5, b = 5;
	int prefix, postfix;

	prefix = (++a) * 3;
	postfix = (b++) * 3;
	printf("prefix=%d, postfix=%d\n", prefix, postfix); //18 15
	printf("a=%d, b=%d\n", a, b);

	printf("전위형: (++a)*3=%d, 후위형: (b++)*3=%d\n", (++a)*3, (b++)*3);

	return 0;
}
