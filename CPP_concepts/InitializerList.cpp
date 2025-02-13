#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

//Function demonstrating read-only access limitation
void modifyInitializerList(initializer_list<int> ilist){
	// Uncommenting the below line will cause compilation error
	// ilist.begin()[0] = 10; // Error: initializer_lit elements are read-only
	//
	cout << "Initializer list elements: ";
	for(int val : ilist){
		cout << val << " ";
	}
	cout << endl;
}

//Function demonstrating fixed-size limitation
void fixedSizeLimit(){
	initializer_list<int> ilist = {1,2,3,4,5};
	// ilist.push_back(6); // Error: initializer_list doesnt support resizing
	
	vector<int> vec = {1,2,3,4,5};
	vec.push_back(6); // Allowed: vector supports dynamic resizing
			  //
	cout << "Vector after push_back: ";
	for(int val: vec){
		cout << val << " ";
	}
	cout << endl;
}

//Function demonstrating no direct indexing limitation
void indexingLimit(){
	initializer_list<int> ilist = {10,20,30};
	// cout << ilist[1]; // Error: initializer_list doesnt support indexing
	
	vector<int> vec = {10,20,30};
	cout << "Vector second element: " << vec[1] << endl; //Allowed
}

//Function demonstrating short lifespan issue
initializer_list<int> createList(){
	return {100,200,300};// Risk: Returning a temporary initializer_list
}

void lifespanIssues(){
	auto ilist = createList(); // list now refers to a temporary object
	cout << "Initializer List elements: ";
	for(int val: ilist){
		cout << val << " ";
	}
	cout <<"(May cause undefined behavior if used outside valid scope)" << endl;
}
int main(){
	cout << "Read-only Access Limitation:" << endl;
	modifyInitializerList({1,2,3});

	cout << "\nFixed size Limitation:" << endl;
	fixedSizeLimit();

	cout << "\nNo Direct indexing Limitation:" << endl;
	indexingLimit();

	cout << "\nShort Lifespan Issue:" << endl;
	lifespanIssues();

	return 0;
}
