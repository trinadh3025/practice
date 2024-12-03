#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>

using namespace std;

//Global variables (stored in the data segment)
int global_var = 42; //Initialized data
int uninit_global_var; //uninitialiezed data (BSS)

void allocateMemory(){
	//Dynamic memory allocation (heap)
	int* heap_array = (int*)malloc(10* sizeof(int));
	if(heap_array == nullptr){
		cout << "Mmory allocation failed!" << endl;
		return;
	}
	
	// Simulate memory usage
	for(int i=0;i<1;i++){
		heap_array[i] = i*2;
		cout << "Heap value[" << i << "] = " << heap_array[i] << endl;
	}

	// Free the allocated memory (to avoid leaks)
}

void stackMemoryExample(int n){
	//Local variables (stored in the stack)
	int stack_array[1000]; // Beware of the large allocations here!

	for(int i=0; i<n; i++){
		stack_array[i] = i+1;
	}

	cout << "Stack allocation successful, sum of first element and last;"
		<< stack_array[0] + stack_array[n-1] << endl;
}

int main(){
	cout << "Global Initialized variable: " << global_var << endl;
	cout << "Global uninitialized variable (default 0):" << uninit_global_var << endl;

	//Demonstrate stack memory usage
	stackMemoryExample(500);

	//Demonstrate heap memory usage
	allocateMemory();

	// Demonstrate heap fragmentation
	cout << "Simulating Fragmentation..." << endl;
	vector<void*> allocations;

	//Allocate and free in irregular patterns
	for(int i=0;i<10;i++){
		void* block = malloc(1024); //allocate 1 kb

		if( i%2 == 0){
			free(block);
		} else{
			allocations.push_back(block);
		}
	}

	cout << "Check your system's memory monitoring tools to observe fragmentation!" << endl;

	char a;
	cin >> a;
	//cleanup remaining allocations
	for(void* ptr : allocations){
		free(ptr);
	}
	return 0;
}
