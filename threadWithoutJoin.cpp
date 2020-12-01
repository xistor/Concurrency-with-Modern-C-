#include <iostream>
#include <thread>
#include <functional>


int fun(int &a) {
    a++;
}

int main(){



std::string s{"C++11"};
int a = 1;
std::thread t1(fun, std::ref(a));
t1.join();
std::thread t2([&]{ std::cout << s << std::endl; });
t2.detach();

std::cout << a << std::endl;

}