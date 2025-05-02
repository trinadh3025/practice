#include <iostream>
#include <mutex>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>


using namespace std;
//Simple thread-safe vector template
template<typename T>
class Vector {
private:
	T* data;
	size_t _size;
	size_t _capacity;
	mutable std::mutex mtx;

	void reallocate(size_t new_capacity){
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < _size; ++i){
			new_data[i] = std::move(data[i]);
		}

		delete[] data;
		data = new_data;
		_capacity = new_capacity;
	}
public:
	//Default constructor
	Vector(): data(nullptr), _size(0), _capacity(0){}

	//Constructor with size
	explicit Vector(size_t count, const T& value = T())
		: data(new T[count]), _size(count), _capacity(count){
		std::fill(data, data+count, value);	
	}

	//Initializer list constructor
	Vector(std::initializer_list<T> init): data(new T[init.size()]), _size(init.size()),
			_capacity(init.size()){
		std::copy(init.begin(), init.end(), data);		
	}

	//Copy constructor
	Vector(const Vector& other){
		std::lock_guard<mutex> lock(other.mtx);
		data = new T[other._capacity];
		_size = other._size;
		_capacity = other._capacity;
		std::copy(other.data, other.data+_size, data);

	}

	//Move constrctor
	Vector(const Vector&& other){
		std::lock_guard<mutex> lock(other.mtx);
		data = other.data;
		_size = other._size;
		_capacity = other._capacity;
		other.data = nullptr;
		other._size = 0;
		other._capacity = 0;
       		       
	}

	//Copy assignment
	Vector& operator=(const Vector& other){
		if (this != &other){
			std::lock_guard<mutex> lock_this(mtx);
			std::lock_guard<mutex> lock_other(other.mtx);
			delete[] data;
			data = new T[other._capacity];
			_size = other._size;
			_capacity = other._capacity;
			std::copy(other.data, other.data + _size, data);
		}
		return *this;
	}

	//Move assignment
	Vector& operator=(Vector&& other) {
		if (this != &other){
			std::lock_guard<mutex> lock_this(mtx);
			std::lock_guard<mutex> lock_other(other.mtx);
			delete[] data;
			data = other.data;
			_size = other._size;
			_capacity = other._capacity;
			other.data = nullptr;
			other._size = 0;
			other._capacity = 0;
		}
		return *this;
	}

	//Destructor
	~Vector(){
		delete[] data;
	}

	//Push back
	void push_back(const T& value){
		std::lock_guard<mutex> lock(mtx);
		if (_size == _capacity){
			reallocate(_capacity == 0 ? 1 : _capacity*2);
		}

		data[_size++] = value;
	}

	//Pop back
	void pop_back(){
		std::lock_guard<mutex> lock(mtx);
		if (_size > 0){
			--_size;
		}
	}

	//Insert at position
	void insert(size_t index, const T& value){
		std::lock_guard<mutex> lock(mtx);
		if (index > _size)
			cout << "Enered index is out of range" << endl;
		if (_size == _capacity){
			reallocate(_capacity == 0 ? 1 : _capacity * 2);
		}
		for (size_t i = _size; i > index; --i){
			data[i] = std::move(data[i-1]);
		}

		data[index] = value;
		++_size;
	}

	//Erase at position
	void erase(size_t index){
		std::lock_guard<mutex> lock(mtx);
		if (index > _size)
			cout << "Enered index is out of range" << endl;
		for (size_t i = index; i< _size-1; ++i){
			data[i] = std::move(data[i+1]);
		}
		--_size;
	}

	//Access operator
	T& operator[](size_t index){
		std::lock_guard<mutex> lock(mtx);
		if (index > _size){
			cout << "Enered index is out of range. Potential crash or undefined behavior" << endl;
		}
		return data[index];
	}

	//Size
	size_t size() const{
		std::lock_guard<mutex> lock(mtx);
		return _size;
	}

	//Capacity
	size_t capacity() const{
		std::lock_guard<mutex> lock(mtx);
		return _capacity;
	}

	//clear
	void clear(){
		std::lock_guard<mutex> lock(mtx);
		_size = 0;
	}

	//Relational operators
	bool operator==(const Vector& other) const{
		std::lock_guard<mutex> lock_this(mtx);
		std::lock_guard<mutex> lock_other(other.mtx);
		if (_size != other._size) return false;
		for (size_t i=0; i < _size; i++){
			if(data[i] != other.data[i]) return false;
		}

		return true;
	}

	bool operator!=(const Vector& other) const{
		return !(*this == other);
	}

	bool operator<(const Vector& other) const{
		std::lock_guard<mutex> lock_this(mtx);
		std::lock_guard<mutex> lock_other(other.mtx);
		size_t min_size = std::min(_size, other._size);
		for (size_t i=0; i < min_size; i++){
			if(data[i] < other.data[i]) return true;
			if(data[i] > other.data[i]) return false;
		}

		return _size < other.size;
		
	}

	bool operator>(const Vector& other) const{
		return other < *this;
	}
};

int main(){
	Vector<int> vec = {1,2,3};
	vec.push_back(4);
	vec.insert(2,99);
	vec.erase(1);

	for(size_t i = 0; i<vec.size(); ++i){
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	Vector<int> vec2 = {1,99,3,4};
	std::cout << (vec == vec2 ? "Equal" : "Not equal") << std::endl;
	std::cout << vec2[6] << endl;
	return 0;
}
