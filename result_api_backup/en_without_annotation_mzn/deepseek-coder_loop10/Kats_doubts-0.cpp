#include <iostream>
#include <algorithm>

int main() {
    int a, b;
    std::cin >> a >> b;

    int max_ans = 2000;
    int ans = max_ans;

    for (int i = max_ans; i >= 1; --i) {
        bool valid = true;
        for (int j = 2; j <= std::min(a, b); ++j) {
            if (a % j == 0 && b % j == 0) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        for (int num_a = 0; num_a <= max_ans / a; ++num_a) {
            for (int num_b = 0; num_b <= max_ans / b; ++num_b) {
                if (num_a * a + num_b * b == i) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }

        if (valid) {
            ans = i;
            break;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}