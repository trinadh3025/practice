#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
mutex mutex1;
mutex mutex2;

/*
 * Deadlock code
 */
#if 0
void thread1(){
	lock_guard<mutex> lock1(mutex1);
	cout << "Thread 1 locked mutex1" << endl;

	this_thread::sleep_for(chrono::milliseconds(100));

	lock_guard<mutex> lock2(mutex2);
	cout << "Thread 1 locked mutex2" << endl;
}

void thread2(){
	lock_guard<mutex> lock1(mutex2);
	cout << "Thread 2 locked mutex2" << endl;

	this_thread::sleep_for(chrono::milliseconds(100));

	lock_guard<mutex> lock2(mutex1);
	cout << "Thread2 locked mutex1" << endl;
}

int main(){
	thread t1(thread1);
	thread t2(thread2);

	t1.join();
	t2.join();

	return 0;
}

#endif

/*
 * Resolution code
 */
#if 1

void thread1(){
	lock(mutex1, mutex2);
	lock_guard<mutex> lock1(mutex1, adopt_lock);
	lock_guard<mutex> lock2(mutex2, adopt_lock);

	cout << "Thread 1 locked mutex1 and mutex2" << endl;
}

void thread2(){
	lock(mutex1, mutex2);
	lock_guard<mutex> lock1(mutex1, adopt_lock);
	lock_guard<mutex> lock2(mutex2, adopt_lock);

	cout << "Thread 2 locked mutex1 and mutex2" << endl;
}

int main(){
	thread t1(thread1);
	thread t2(thread2);

	t1.join();
	t2.join();

	return 0;
}



#endif
