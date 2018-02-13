#include <iostream>
#include <chrono>

using namespace std::chrono;

int main () {
    auto ms1 = system_clock::now();
    for (int i = 0; i < 1000000000; i++) {
        int j = i + i * i;
    }
    auto ms2 = system_clock::now();
    std::chrono::duration<float> duration = ms2 - ms1;
    std::cout << duration.count() << std::endl;
}
