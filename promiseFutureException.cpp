#include <exception>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

#ifdef WIN32
#include <string>
#endif

struct Div {
  void operator()(std::promise<int>&& intPromise, int a, int b){
    //try {
      if (b == 0) {
        std::string errMess = std::string("Illegal division by zero: ") +
          std::to_string(a) + "/" + std::to_string(b);
        intPromise.set_exception(std::make_exception_ptr(std::runtime_error(errMess)));
        return;
      }
      
      intPromise.set_value(a / b);
    //}
    // catch (...) {
    //     std::cout << "div exception" << std::endl;
    //   intPromise.set_exception(std::current_exception());
    // }
  }
};

void executeDivision(int nom, int denom) {
  std::promise<int> divPromise;
  std::future<int> divResult = divPromise.get_future();

  Div div;
  std::thread divThread(div, std::move(divPromise), nom, denom);

  // get the result or the exception
  try {
    std::cout << nom << "/" << denom << " = " << divResult.get() << std::endl;
  }
  catch (std::runtime_error& e) {
    std::cout << "exception:" << std::endl;
    std::cout << e.what() << std::endl;
  }

  divThread.join();
}

int main() {

  std::cout << std::endl;

  executeDivision(20, 0);
  executeDivision(20, 10);

  std::cout << std::endl;

}