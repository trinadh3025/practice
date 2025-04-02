#include <iostream>

using namespace std;

void counter(){
	static int count = 0; // Retains value between calls
	count++;
	cout << "Count: " << count << endl;
}

int main(){

	counter(); //counter 1
	counter(); //counter 2
	
	auto x = 10; //Automatically deduces type (int)
        auto y = 3.14; //Automaticall deduces type (float)
        
	cout << "x: " << x << ", " << "y: " << y << endl;
	return 0;
}
