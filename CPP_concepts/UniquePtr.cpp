#include <iostream>
#include <utility>

using namespace std;

template<typename T>
class UniquePtr{
	T* ptr;
public:
	explicit UniquePtr(T* p = nullptr) : ptr(p) {}

	//Move constructor
	UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr){
		other.ptr = nullptr;
	}

	//Move assignment
	UniquePtr& operator=(UniquePtr&& other) noexcept {
		if (this != &other){
			delete ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}

	//Delete copy constructor and copy assignment
	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	~UniquePtr(){
		delete ptr;
	}

	T& operator*() const { return *ptr;}
	T* operator->() const { return ptr; }
	T* get() const { return ptr; }

	T* release() {
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}

	void reset(T* p = nullptr){
		delete ptr;
		ptr = p;
	}

	explicit operator bool() const {
		return ptr != nullptr;
	}
};


int main(){
	UniquePtr<int> uptr(new int(10));
	cout << "UniquePtr value: " << *uptr << endl;

	UniquePtr<int> moved = move(uptr);
	if(!uptr)
		cout << "uptr is null after move" << endl;

	return 0;
}
