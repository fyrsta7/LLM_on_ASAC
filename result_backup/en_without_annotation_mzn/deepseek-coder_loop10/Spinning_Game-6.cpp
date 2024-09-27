#include <iostream>
#include <vector>

int main() {
    int n, m, k, x;
    std::cin >> n >> m >> k >> x;

    long long rounds = 1;
    for (int i = 0; i < k; ++i) {
        rounds *= 10;
    }

    std::vector<int> seen(n, -1);
    std::vector<int> states;
    int current = x;

    for (long long i = 0; i <= rounds; ++i) {
        if (seen[current] != -1) {
            int cycle_start = seen[current];
            int cycle_length = i - cycle_start;
            int remaining_rounds = (rounds - cycle_start) % cycle_length;
            std::cout << states[cycle_start + remaining_rounds] << std::endl;
            return 0;
        }
        seen[current] = i;
        states.push_back(current);
        current = (current + m) % n;
    }

    std::cout << current << std::endl;
    return 0;
}