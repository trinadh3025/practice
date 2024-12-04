#include <iostream>
using namespace std;

class Base{
	int x;
public:
	Base(){std::cout << "Constructor:" << std::endl;}
	~Base(){std::cout << "Destructor:" << std::endl;}
};

int main(){
	//Normal case
	std::cout << "Normal case:" << std::endl;
	Base *obj = new Base();
	int *cha;
	cha = (int*)malloc(10);
	delete obj;

	//placement new
	std::cout << "placement new case:" << std::endl;
	char *memory = new char[10*sizeof(Base)];

	Base *obj1 = new (&memory[0])Base();
	Base *obj2 = new (&memory[4])Base();
	Base *obj3 = new (&memory[8])Base();

	obj1->~Base();
	obj2->~Base();
	obj3->~Base();

	delete[] memory;
	return 0;
}
