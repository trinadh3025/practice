#include<iostream>
using namespace std;

class Base{
	int x;
public:
	Base(){}
	Base(int x) : x(x) {}
private:
	Base* operator & (){
		return this;
	}
};

int main(){
	Base b;
	Base *bp = &b;
	return 0;
}
