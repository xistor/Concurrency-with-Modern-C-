#include <execution>
#include <vector>
#include <mutex>

std::mutex m;

int main() {

  std::vector<int> v = { 1, 2, 3 };

  int sum = 0;
  std::for_each(std::execution::par_unseq, v.begin(), v.end(), [&sum](int i) {
    std::lock_guard<std::mutex> lock(m);
    sum += i + i;
    });

}