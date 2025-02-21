#include <iostream>
using namespace std;

int main(){
	
	int m=3, n=4, c=0;

	int* arr = new int[m*n];

	/*
	 *
	 * int** a = new int*[m];
	 * for( in all rows)
	 * a[i] = new int[n];
	 *
	 * at end individual row should be deleted
	 * for(rows)
	 * delte[] a[i]
	 *
	 * delte[] a;
	 */

	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			*(arr + i * n + j) = ++c;
		}
	}

	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			cout << *(arr + i * n + j) << " ";
		}
		cout << endl;
	}

	delete[] arr;
	return 0;
}
