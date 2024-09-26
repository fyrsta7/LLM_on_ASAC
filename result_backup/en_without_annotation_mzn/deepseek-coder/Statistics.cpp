#include <iostream>
#include <vector>

int countTwos(int x) {
    int count = 0;
    while (x > 0) {
        if (x % 10 == 2) count++;
        x /= 10;
    }
    return count;
}

int main() {
    int l, r;
    std::cin >> l >> r;

    int answer = 0;
    for (int i = l; i <= r; ++i) {
        answer += countTwos(i);
    }

    std::cout << answer << std::endl;
    return 0;
}