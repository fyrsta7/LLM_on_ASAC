#include <iostream>
#include <vector>

int main() {
    std::vector<int> apple = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int h = 50;
    int num = 0;

    for (int i = 0; i < 10; ++i) {
        if (apple[i] <= h + 30) {
            ++num;
        }
    }

    std::cout << num << std::endl;
    return 0;
}