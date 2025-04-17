#include<stdio.h>

int main(){

	int a, position;

	printf("Enter the number and bit position to toggle\n");

	scanf("%d%d", &a, &position);
	
	a = a^(1<<(position-1));
	printf("%d\n", a);

	int x,y;
	printf("Enter the numbers to swap\n");

	scanf("%d%d", &x, &y);

	x = x+y;
	y = x-y;
	x = x-y;

	printf("after swap x:%d, y:%d\n", x,y);
	

	return 0;
}
