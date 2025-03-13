#include <iostream>
#include <mutex>

using namespace std;

class Singleton{
public:
	//Delete copy constructor and assignment operator
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	// Pubic static method to access the instance
	static Singleton& getInstance(){
		std::lock_guard<mutex> lock(mutex_);
		if(instance_ == nullptr){
			instance_ = new Singleton();		
		} else{
			cout << "Couldn't create instance as its already an instance exists" << endl;
		}
		return *instance_;
	}

	void sayHello() const{
		cout << "Hello, Singleton.!" << endl;
	}

private:
	//Private constructor to prevent external instantiation
	Singleton(){
		cout << "Singleton instance created." << endl;
	}

	~Singleton(){
		cout << "Singleton instance destroyed" << endl;
	}

	static Singleton* instance_;
	static std::mutex mutex_;
};

Singleton* Singleton::instance_ = nullptr;
std::mutex Singleton::mutex_;

int main(){
	Singleton& instance = Singleton::getInstance();
	instance.sayHello();
	Singleton& instance2 = Singleton::getInstance();
	instance2.sayHello();

	cout << "inst1 - " << &instance << endl;
	cout << "inst2 - " << &instance2 << endl;
	

	return 0;
}
