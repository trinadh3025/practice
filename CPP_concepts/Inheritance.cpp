#include <iostream>
#include <cstring>
using namespace std;

class Base{
public:
	int baseData1;
	char baseData2[3];

	Base(int a=0, char b=0):baseData1(a){
		memset(baseData2, b, sizeof(baseData2));
		cout << "Base constructor" << endl;
	}

	virtual void show(){
		cout << "Base show: " << baseData1 << ", " << baseData2 << endl;
	}

	virtual ~Base(){
		cout << "Base Destructor" << endl;
	}
};

class Derived1 : virtual public Base{
public:
	float derivedData1;

	Derived1(float a=0.0f):derivedData1(a){
		cout << "Derived1 constructor" << endl;
	}

	void show() override{
		cout << "Derived1 show: " << baseData1 << ", " << baseData2 << ", " << derivedData1 << endl;
	}

	~Derived1() override{
		cout << "Derived1 destructor" << endl;
	}
};

class Derived2 : virtual public Base{
public:
	double derivedData2;

	Derived2(double a=0.0):derivedData2(a){
		cout << "Derived2 constructor" << endl;
	}

	void show() override{
		cout << "Derived2 show: " << baseData1 << ", " << baseData2 << ", " << derivedData2 << endl;
	}

	~Derived2() override{
		cout << "Derived2 destructor" << endl;
	}
};

class MultiDerived : public Derived1, public Derived2{
public:
	bool multiDerivedData;

	MultiDerived(bool a=false):multiDerivedData(a){
		cout << "MultiDerived constructor" << endl;
	}

	void show() override{
		cout << "MultiDerived show: " << baseData1 << ", " << baseData2 << ", " << derivedData1 << ", " << derivedData2 << ", " << multiDerivedData << endl;
	}

	~MultiDerived() override{
		cout << "MultiDerived destructor" << endl;
	}
};

int main(){
	Base obj1(2, 66);
	Derived1 obj2(3.0);
	Derived2 obj3(4.0);
	MultiDerived obj4(true);
	obj1.show();
	obj2.show();
	obj3.show();
	obj4.show();

	return 0;
}
