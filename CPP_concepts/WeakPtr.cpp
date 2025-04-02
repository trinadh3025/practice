#include<iostream>
#include<memory>
using namespace std;

struct Child;

struct Parent{
	std::shared_ptr<Child> child;
	~Parent(){
		std::cout << "Parent distroyed\n" ;
	}
};

struct Child{
	std::weak_ptr<Parent> parent;
	~Child(){
		std::cout << "Child destroyed\n";
	}
};

int main(){
	std::shared_ptr<Parent> parent = std::make_shared<Parent>();
	std::shared_ptr<Child> child = std::make_shared<Child>();

	parent->child = child;
	child->parent = parent;//No cyclic reference due to weak_ptr

	return 0;
}
