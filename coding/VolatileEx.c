#include <stdio.h>

int funA(){
	static int a = 10;
}

int funB(){
	static int a = 11;
}

int main(void){
	const volatile int local = 10;
	int *ptr = (int*) &local;

	printf("Initial value of local : %d\n", local);

	*ptr = 100;
	printf("Modified value of local : %d\n", local);
	return 0;
}
