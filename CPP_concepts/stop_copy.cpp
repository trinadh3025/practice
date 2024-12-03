#include <iostream>
using namespace std;

class StopCopy{
public:
	StopCopy(){}
private:
	StopCopy(const StopCopy &obj){}
	StopCopy& operator = (const StopCopy& rhs){}
};

class Base : public StopCopy{
	int _x;
public:
	Base() : _x{0}{}
	Base(int x) : _x{x} {}
};

int main(){
	Base b1(10);
	//Base b2 = b1;
	return 0;
}
