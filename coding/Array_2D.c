#include<stdio.h>
#include<stdlib.h>

int main(){
	
	int arr1[5][5] = {{0,1,2,3,4},
			  {2,3,4,5,6},
			  {4,5,6,7,8},
			  {6,7,8,9,10},
			  {8,9,10,11,12}};

	int*** arr2 = malloc(5*sizeof(int**));
	for(int i=0;i<5;i++)
		arr2[i] = malloc(5*sizeof(int*));

	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++)
			arr2[i][j] = &arr1[i][j];
	}

	printf("The values are \n");

	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++)
			printf("%d ", *arr2[i][j]);
		printf("\n");
	}

	return 0;
}
