#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

int main() {
    int N, m1, m2;
    std::cin >> N >> m1 >> m2;
    std::vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> S[i];
    }

    int M = std::pow(m1, m2);
    int max_T = 10000;
    std::vector<int> time(N, max_T);
    int ans = max_T;

    for (int i = 0; i < N; ++i) {
        for (int t = 1; t <= max_T; ++t) {
            if (std::pow(S[i], t) % M == 0) {
                time[i] = t;
                break;
            }
        }
        ans = std::min(ans, time[i]);
    }

    if (ans == max_T) {
        std::cout << "-1" << std::endl;
    } else {
        std::cout << ans << std::endl;
    }
    
    return 0;
}
