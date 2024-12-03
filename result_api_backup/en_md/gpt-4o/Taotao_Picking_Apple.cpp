#include <iostream>

int main() {
    int heights[10];
    int maxHeight;

    for (int i = 0; i < 10; ++i) {
        std::cin >> heights[i];
    }
    std::cin >> maxHeight;

    int reachableHeight = maxHeight + 30;
    int count = 0;

    for (int i = 0; i < 10; ++i) {
        if (heights[i] <= reachableHeight) {
            ++count;
        }
    }

    std::cout << count << std::endl;
    return 0;
}