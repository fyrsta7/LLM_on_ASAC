#include <iostream>
#include <vector>

int main() {
    std::vector<int> appleHeights(10);
    for (int i = 0; i < 10; i++) {
        std::cin >> appleHeights[i];
    }
    int maxReach;
    std::cin >> maxReach;

    int benchHeight = 30;
    int totalReach = maxReach + benchHeight;
    int count = 0;

    for (int height : appleHeights) {
        if (height <= totalReach) {
            count++;
        }
    }

    std::cout << count << std::endl;
    return 0;
}