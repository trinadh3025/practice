#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <vector>

class MutexExample {
    std::mutex mtx;
    int counter = 0;

public:
    void increment() {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
        std::cout << "MutexExample Counter: " << counter << "\n";
    }
};

class RecursiveMutexExample {
    std::recursive_mutex rec_mtx;
    int depth = 0;

public:
    void recursiveFunction(int level) {
        if (level == 0) return;

        std::lock_guard<std::recursive_mutex> lock(rec_mtx);
        depth++;
        std::cout << "Recursive depth: " << depth << "\n";
        recursiveFunction(level - 1);
    }
};

class TimedMutexExample {
    std::timed_mutex timed_mtx;

public:
    void tryLockExample() {
        if (timed_mtx.try_lock_for(std::chrono::milliseconds(100))) {
            std::cout << "TimedMutexExample locked successfully.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            timed_mtx.unlock();
        } else {
            std::cout << "TimedMutexExample failed to lock.\n";
        }
    }
};

class SharedMutexExample {
    std::shared_mutex shared_mtx;
    int shared_data = 0;

public:
    void reader() {
        std::shared_lock<std::shared_mutex> lock(shared_mtx);
        std::cout << "SharedMutexExample Read: " << shared_data << "\n";
    }

    void writer() {
        std::unique_lock<std::shared_mutex> lock(shared_mtx);
        shared_data++;
        std::cout << "SharedMutexExample Write: " << shared_data << "\n";
    }
};

void uniqueLockExample(std::mutex& mtx) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "UniqueLockExample: Locked\n";
    lock.unlock();
    std::cout << "UniqueLockExample: Unlocked\n";
}

int main() {
    // 1. std::mutex example
    MutexExample mutexExample;
    std::thread t1([&]() { mutexExample.increment(); });
    std::thread t2([&]() { mutexExample.increment(); });

    // 2. std::recursive_mutex example
    RecursiveMutexExample recursiveExample;
    std::thread t3([&]() { recursiveExample.recursiveFunction(3); });

    // 3. std::timed_mutex example
    TimedMutexExample timedExample;
    std::thread t4([&]() { timedExample.tryLockExample(); });
    std::thread t5([&]() { timedExample.tryLockExample(); });

    // 4. std::shared_mutex example
    SharedMutexExample sharedExample;
    std::thread t6([&]() { sharedExample.writer(); });
    std::thread t7([&]() { sharedExample.reader(); });
    std::thread t8([&]() { sharedExample.reader(); });

    // 5. std::unique_lock example
    std::mutex mtx;
    std::thread t9([&]() { uniqueLockExample(mtx); });

    // Join all threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();

    return 0;
}

