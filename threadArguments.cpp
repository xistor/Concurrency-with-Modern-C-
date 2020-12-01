
#include <chrono>
#include <iostream>
#include <thread>

class Sleeper {
public:
  Sleeper(int& i_) :i{ i_ } {};
  void operator()(int k) {
    for (unsigned int j = 0; j <= 5; ++j) {
      std::this_thread::sleep_for(std::chrono::microseconds(100));
      i += k;
    }
    std::cout << std::this_thread::get_id() << std::endl;
  }
private:
  int& i;
};


int main() {

  std::cout << std::endl;

  int valSleepr = 1000;
  std::thread t(Sleeper(valSleepr), 5);
  t.join();
  std::cout << "valSleeper = " << valSleepr << std::endl;
  std::cout << "num of thead: " << std::thread::hardware_concurrency() << std::endl;


}