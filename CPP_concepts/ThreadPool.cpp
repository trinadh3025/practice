#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<random>

using namespace std;

class ThreadPool{
public:
	//constructor to creates a threadpool with give number of threads
	ThreadPool(size_t num_threads = thread::hardware_concurrency()){
		for(size_t i=0;i<num_threads; ++i){
			threads_.emplace_back([this]{
				while(true){
					function<void()> task;
					//in below block, to unlock the queue before
					//executing the task so that other threads
					//can perform enqueue tasks
					{
						//Locking the queue so that data can be shared
						unique_lock<mutex> lock(queue_mutex_);

						//waiting until there is a task to execute
						//or the pool is stopped
						cv_.wait(lock, [this]{
							return !tasks_.empty() || stop_;
							});

						//exit the thread in the case of pool is stopped
						//and there are no task
						if(stop_ && tasks_.empty()){
							return;
						}

						//get the next task from the queue
						task = move(tasks_.front());
						tasks_.pop();
					}
					task();

				}	
			});
		}
	}
	
	//Destructor to stop the thread pool	
	~ThreadPool(){
		{
			//Lock the queue to update the stop flag safely
			unique_lock<mutex> lock(queue_mutex_);
			stop_ = true;
		}
		
		//Notify all threads
		cv_.notify_all();
		
		//Joining all worker threads to ensure they have completed 
		//their tasks
		for(auto& thread: threads_){
			thread.join();
		}
	}
	
	//Enqueue task for execution by the thread pool
	void enqueue(function<void()> task){
		{
			unique_lock<std::mutex> lock(queue_mutex_);
			tasks_.emplace(move(task));
		}
		cv_.notify_one();
	}
private:
	//Vector to store worker threads
	vector<thread> threads_;

	//Queue of tasks
	queue<function<void()>> tasks_;

	//Mutex to synchronize access to shared data
	mutex queue_mutex_;

	//Condition variable to signal changes in the 
	//state of the tasks queue
	condition_variable cv_;

	//Flag to indicate whether the thread pool should
	//stop or not
	bool stop_ = false;
};

int main(){
	
	/*
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrub(65,92);
	*/
	ThreadPool pool(4);

	for(int i=0; i<5; ++i){
	        //int random_num = distrub(gen);
		pool.enqueue([i]{
			cout << "Task " << i << " is running on thread" << this_thread::get_id() << endl;
			//work
			this_thread::sleep_for(chrono::milliseconds(100));
		});
	}

	return 0;
}
