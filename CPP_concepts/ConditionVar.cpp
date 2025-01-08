#include<iostream>
#include<thread>
#include<condition_variable>

using namespace std;

/*
 program that creates two threads to print even and odd numbers in order 
 using std::condition_variable for synchronization
 */
class NumberPrinter{
public:
	NumberPrinter(int max): max_number(max), current(1){}

	void printOdd(){
		while(current <= max_number){
			std::unique_lock<std::mutex> lock(mutex_);
			cv_.wait(lock, [this]() { return current%2 == 1 || current > max_number;});

			if(current > max_number) break;

			std::cout << current << std::endl;
			++current;

			cv_.notify_all();
		}		
	}

	void printEven(){
		while(current <= max_number){
			std::unique_lock<std::mutex> lock(mutex_);
			cv_.wait(lock, [this]() { return current%2 == 0 || current > max_number;});

			if(current > max_number) break;

			std::cout << current << std::endl;
			++current;

			cv_.notify_all();
		}		
	
	}

private:
	int max_number;
	int current;
	std::mutex mutex_;
	std::condition_variable cv_;
};

int main(){
	const int max_number = 10;
	NumberPrinter printer(max_number);

	std::thread odd_thread(&NumberPrinter::printOdd, &printer);
	std::thread even_thread(&NumberPrinter::printEven, &printer);

	odd_thread.join();
	even_thread.join();

	return 0;
}
