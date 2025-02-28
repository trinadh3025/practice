#include <iostream>

using namespace std;

//Template function
template <typename T>
void staticFunction(){
	static int counter = 0; //Static varaible inside a template function
	counter++;
	cout << "Counter for type " << typeid(T).name() << ": " << counter << endl;
}

//Template class
template <typename T>
class StaticClass{
public:
	static int counter;
	void increment(){
		counter++;
	}

	void show(){
		cout << "Counter for type " << typeid(T).name() << ": " << counter << endl;
	}
};

//Definition of static member variable
template <typename T>
int StaticClass<T>::counter = 0;

//Non-type Template function
template<int N>
void staticFunction_NT(){
	static int counter = 0;
	counter++;
	cout << "Counter for N=" << N << ": " << counter << endl;
}

//Specialized Template
template<typename T>
class SpecialStatic{
public:
	static int counter;
};

template<typename T>
int SpecialStatic<T>::counter = 0;

template<>
int SpecialStatic<int>::counter = 100; //Separate specialization with a different counter

int main(){

	staticFunction<int>(); //Instantiation staticFunction<int>
	staticFunction<int>(); //Uses the same static variable as previous call
	staticFunction<double>();//Instantiates statifFunction<double> (new counter)
	staticFunction<double>();//Uses the same static variable from previous

	StaticClass<int> obj1, obj2;
	obj1.increment();
	obj2.increment();
	obj1.show(); //Shared counter for int
		     
	StaticClass<double> objd1, objd2;
	objd1.increment();
	objd2.increment();
	objd1.show(); //Shared counter for double
		      //
	staticFunction_NT<1>();
	staticFunction_NT<1>();
	staticFunction_NT<2>();//Different template instantiation
	staticFunction_NT<2>();

	SpecialStatic<double>::counter++;
	SpecialStatic<double>::counter++;

	SpecialStatic<int>::counter++;//This starts at 100
	
	cout << "Counter for double: " << SpecialStatic<double>::counter << endl;
	cout << "Counter for int: " << SpecialStatic<int>::counter << endl;

	return 0;
}
