#include <future>
#include <iostream>
#include <utility>

void doWork() {
    std::cout << "Processing shared data." << std::endl;
}

void waitingForWork(std::future<void>&& fut) {

    std::cout << "Worker: waiting for work." << std::endl;
    fut.wait();
    doWork();
    std::cout << "work done." << std::endl;
}


void setDataReady(std::promise<void>&& prom) {

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Sender: Data is Ready." << std::endl;
    prom.set_value();
}

int main() {
    
    std::promise<void> sendReady;
    auto fut = sendReady.get_future();

    std::thread t1(waitingForWork, std::move(fut));
    std::thread t2(setDataReady, std::move(sendReady));

    t1.join();
    t2.join();

}
