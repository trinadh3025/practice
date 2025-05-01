#include <iostream>
#include <mutex>
#include <utility>

using namespace std;

template<typename T>
class SharedPtr{
	T* ptr;
	int* ref_count;
	mutex* mtx;
	
	void release(){
		bool should_delete = false;

		if(ref_count && mtx){
			lock_guard<mutex> lock(*mtx);
			--(*ref_count);
			if (*ref_count == 0){
				should_delete = true;
			}
		}

		if(should_delete){
			delete ptr;
			delete ref_count;
			delete mtx;
		}

		ptr = nullptr;
		ref_count = nullptr;
		mtx = nullptr;
	}

public:
	explicit SharedPtr(T* p = nullptr):
		ptr(p), ref_count(new int(1)), mtx(new mutex){}

	//Copy constructor
	SharedPtr(const SharedPtr& other){
		ptr = other.ptr;
		ref_count = other.ref_count;
		mtx = other.mtx;

		lock_guard<mutex> lock(*mtx);
		++(*ref_count);
	}

	//Move constructor
	SharedPtr(SharedPtr&& other) noexcept
		: ptr(other.ptr), ref_count(other.ref_count), mtx(other.mtx) {
		other.ptr = nullptr;
		other.ref_count = nullptr;
		other.mtx = nullptr;
		}

	//Copy assignment
	SharedPtr& operator=(const SharedPtr& other){
		if (this != &other){
			release();
			ptr = other.ptr;
			ref_count = other.ref_count;
			mtx = other.mtx;

			lock_guard<mutex> lock(*mtx);
			++(*ref_count);
		}
		return *this;
	}

	//Move assignment
	SharedPtr& operator=(SharedPtr&& other) noexcept{
		if (this != &other){
			release();
			ptr = other.ptr;
			ref_count = other.ref_count;
			mtx = other.mtx;

			other.ptr = nullptr;
			other.ref_count = nullptr;
			other.mtx = nullptr;
		}

		return *this;
	}

	~SharedPtr(){
		release();
	}

	T& operator*() const {return *ptr;}
	T* operator->() const {return ptr;}
	T* get() const {return ptr;}

	int use_count() const{
		if(ref_count && mtx){
			lock_guard<mutex> lock(*mtx);
			return *ref_count;
		}
		return 0;
	}

	void reset(T* p=nullptr){
		release();
		ptr = p;
		ref_count = new int(1);
		mtx = new mutex;
	}

	explicit operator bool() const noexcept{
		return ptr != nullptr;
	}
};

int main(){
	SharedPtr<int> sp1(new int(100));
	SharedPtr<int> sp2 = sp1;

	cout << "SharedPtr1: " << *sp1 << " | count: " << sp1.use_count() << endl;
	cout << "SharedPtr2: " << *sp2 << " | count: " << sp2.use_count() << endl;

	return 0;
}
