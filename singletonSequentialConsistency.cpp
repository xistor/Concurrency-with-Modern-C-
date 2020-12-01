// singletonSequentialConsistency.cpp

#include <atomic>
#include <iostream>
#include <future>
#include <mutex>
#include <thread>

constexpr auto tenMill = 10000000;

class MySingleton {
public:
    static MySingleton* getInstance() {
        MySingleton* sin = instance.load();
        if (!sin) {
            std::lock_guard<std::mutex> mylock(myMutex);
            sin = instance.load(std::memory_order_relaxed);
            if(!sin) {
                sin = new MySingleton();
                instance.store(sin);
            }
        }

        return sin;
    }

private:

    MySingleton() = default;
    ~MySingleton() = default;
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;

    static std::atomic<MySingleton*> instance;
    static std::mutex myMutex;

};


std::atomic<MySingleton*> MySingleton::instance;
std::mutex MySingleton::myMutex;


int main() {


}