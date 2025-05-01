#include <iostream>
#include <mutex>
#include <utility>

using namespace std;

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr;

template <typename T>
struct ControlBlock{
	T* ptr;
	int strong_count;
	int weak_count;
	mutex mtx;

	ControlBlock(T* p) : ptr(p), strong_count(1), weak_count(0) {}
};

template <typename T>
class SharedPtr {
	ControlBlock<T>* ctrl;

	void release(){
		if(ctrl){
			lock_guard<mutex> lock(ctrl->mtx);
			if (--(ctrl->strong_count) == 0){
				delete ctrl->ptr;
				ctrl->ptr = nullptr;
				if (ctrl->weak_count == 0)
					delete ctrl;
			}
			ctrl = nullptr;
		}
	}
	
	explicit SharedPtr(ControlBlock<T>* block, bool flag = true):ctrl(block){}
	explicit SharedPtr(ControlBlock<T>* block):ctrl(block){
		cout << "Entered SharedPtr(controlBlock)" << endl;
		if (ctrl) {
		        cout << "Locking ctrl->mtx" << endl;
			lock_guard<mutex> lock(ctrl->mtx);
		        cout << "Locked ctrl->mtx" << endl;
			++ctrl->strong_count;
		}
	}
public:
	explicit SharedPtr(T* p=nullptr) : ctrl(nullptr){
		if (p) {
			ctrl = new ControlBlock<T>(p);
		}
	}

	SharedPtr(const SharedPtr& other){
		ctrl = other.ctrl;
		if (ctrl) {
			lock_guard<mutex> lock(ctrl->mtx);
			++ctrl->strong_count;
		}
	}


	SharedPtr(SharedPtr&& other) noexcept {
		ctrl = other.ctrl;
		other.ctrl = nullptr;
	}

	SharedPtr& operator=(const SharedPtr& other){
		if (this != &other){
			release();
			ctrl = other.ctrl;
			if(ctrl){
				lock_guard<mutex> lock(ctrl->mtx);
				++ctrl->strong_count;
			}
		}

		return *this;
	}

	SharedPtr& operator=(nullptr_t){
		release();
		ctrl = nullptr;
		return *this;
	}

	SharedPtr& operator=(SharedPtr&& other) noexcept {
		if (this != &other){
			release();
			ctrl = other.ctrl;
			other.ctrl = nullptr;
		}

		return *this;
	}

	~SharedPtr(){
		release();
	}

	T& operator*() const { return *(ctrl->ptr);}
	T* operator->() const { return ctrl->ptr; }
	T* get() const { return ctrl ? ctrl->ptr : nullptr;}

	int use_count() const{
		if (ctrl){
			lock_guard<mutex> lock(ctrl->mtx);
			return ctrl->strong_count;
		}
		return 0;
	}

	bool unique() const{
		return use_count() == 1;
	}

	bool expired() const{
		return !ctrl || ctrl->strong_count == 0;
	}

	friend class WeakPtr<T>;
};

template <typename T>
class WeakPtr {
	ControlBlock<T>* ctrl;

public:
	WeakPtr() : ctrl(nullptr){}

	WeakPtr(const SharedPtr<T>& shared) {
		ctrl = shared.ctrl;
		if (ctrl) {
			lock_guard<mutex> lock(ctrl->mtx);
			++ctrl->weak_count;
		}
	}

	WeakPtr(const WeakPtr& other){
		ctrl = other.ctrl;
		if (ctrl) {
			lock_guard<mutex> lock(ctrl->mtx);
			++ctrl->weak_count;
		}
	}

	WeakPtr(WeakPtr&& other) noexcept{
		ctrl = other.ctrl;
		other.ctrl = nullptr;
	}

	WeakPtr& operator=(const WeakPtr& other){
		if (this != &other){
			release();
			ctrl = other.ctrl;
			if (ctrl) {
				lock_guard<mutex> lock(ctrl->mtx);
				++ctrl->weak_count;
			}
		}

		return *this;
	}

	WeakPtr& operator=(WeakPtr&& other) noexcept{
		if (this != &other){
			release();
			ctrl = other.ctrl;
			other.ctrl = nullptr;
		}

		return *this;
	}

	~WeakPtr(){
		release();
	}

	void release(){
		if (ctrl) {
			lock_guard<mutex> lock(ctrl->mtx);
			if (--ctrl->weak_count == 0 && ctrl->strong_count == 0){
				delete ctrl;
			}
			ctrl = nullptr;
		}
	}

	bool expired() const{
		return !ctrl || ctrl->strong_count == 0;
	}

	SharedPtr<T> lock() const{
		if (ctrl) {
			cout << "Trying to lock ctrl->mtx" << endl;
			lock_guard<mutex> lock(ctrl->mtx);
			cout << "ctrl->mtx is locked" << endl;
			if (ctrl->strong_count > 0){
			        cout << "returning control block to sharePtr" << endl;
				return SharedPtr<T>(ctrl,true);
			}
		}
		return SharedPtr<T>();
	}
};

int main(){
	SharedPtr<int> sp(new int(42));
	WeakPtr<int> wp(sp);

	cout << "Shared count: " << sp.use_count() << endl;
	auto locked = wp.lock();	
	if (locked.get()){
		cout << "WeakPtr locked value: " << *locked << endl;
	}

	sp = nullptr;

	if(wp.expired()){
		cout << "WeakPtr expired after SharedPtr reset." << endl;
	}

	return 0;
}
