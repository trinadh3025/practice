#include <iostream>
#include <memory>

class MyClass{
public:
	MyClass(int val): value(val){
		std::cout << "Constructor: " << value << std::endl;
	}

	~MyClass(){
		std::cout << "Destructor: " << value << std::endl;
	}

	void display(){
		std::cout << "Value: " << value << std::endl;
	}

private:
	int value;
};

void uniquePtrExample(){
	std::cout << "\n---- unique_ptr Example ------\n";
	std::unique_ptr<MyClass> ptr1(new MyClass(1));
	ptr1->display();

	//Transfer ownership using std::move
	std::unique_ptr<MyClass> ptr2 = std::move(ptr1);
	if (!ptr1){
		std::cout << "ptr1 is no null after move\n";
	}
	ptr2->display();
}

void sharedPtrExample(){
	std::cout << "\n---- shared_ptr Example -----\n";
	std::shared_ptr<MyClass> sp1 = std::make_shared<MyClass>(2);
	std::shared_ptr<MyClass> sp2 = sp1; //Shared ownership
	std::cout << "Use cound: " << sp1.use_count() << std::endl;

	sp1->display();
	sp2->display();
}

void weakPtrExample(){
	std::cout << "\n---- weak_ptr Example ----\n";
	std::shared_ptr<MyClass> sp = std::make_shared<MyClass>(3);
	std::weak_ptr<MyClass> wp = sp;

	std::cout << "Use count (shared): " << sp.use_count() << std::endl;

	if(auto temp = wp.lock()){
		std::cout << "weak_ptr is valid. Use cound: " << temp.use_count() << std::endl;
		temp->display();
	}else{
		std::cout << "weak_ptr expired.\n";
	}

	sp.reset(); //destroy the shared_ptr
		    //
	if( wp.expired()){
		std::cout << "weak_ptr expired after shared_ptr reset.\n";
	}
}

int main(){
	uniquePtrExample();
	sharedPtrExample();
	weakPtrExample();

	return 0;
}
