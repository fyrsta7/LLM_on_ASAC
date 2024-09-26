#include <iostream>
#include <array>

int main() {
    std::array<int, 10> apple;
    int h;
    for (int i = 0; i < 10; ++i) {
        std::cin >> apple[i];
    }
    std::cin >> h;

    int num = 0;
    for (int i = 0; i < 10; ++i) {
        if (apple[i] <= h + 30) {
            ++num;
        }
    }

    std::cout << num << std::endl;
    return 0;
}