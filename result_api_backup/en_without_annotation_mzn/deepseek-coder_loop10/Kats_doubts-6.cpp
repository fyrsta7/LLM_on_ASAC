#include <iostream>
#include <algorithm>

int main() {
    int a, b;
    std::cin >> a >> b;

    int max_ans = 2000;
    int ans = max_ans;

    for (int i = 2; i <= std::min(a, b); ++i) {
        if (a % i == 0 && b % i == 0) {
            ans = 0;
            break;
        }
    }

    if (ans != 0) {
        for (int num_a = 0; num_a <= max_ans; ++num_a) {
            for (int num_b = 0; num_b <= max_ans; ++num_b) {
                if (num_a * a + num_b * b <= max_ans) {
                    ans = std::min(ans, num_a * a + num_b * b);
                }
            }
        }
    }

    std::cout << ans << std::endl;
    return 0;
}