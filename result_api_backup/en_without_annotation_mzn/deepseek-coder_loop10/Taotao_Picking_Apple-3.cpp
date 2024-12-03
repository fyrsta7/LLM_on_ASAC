#include <iostream>
#include <vector>

int main() {
    std::vector<int> apple = {/* Initialize with 10 integers */};
    int h = /* Initialize with an integer */;
    int num = 0;

    for (int i = 0; i < 10; ++i) {
        if (apple[i] <= h + 30) {
            ++num;
        }
    }

    std::cout << num << std::endl;
    return 0;
}