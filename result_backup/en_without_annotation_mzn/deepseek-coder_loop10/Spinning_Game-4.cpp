#include <iostream>
#include <vector>

int main() {
    int n, m, k, x;
    std::cin >> n >> m >> k >> x;

    long long rounds = 1;
    for (int i = 0; i < k; ++i) {
        rounds *= 10;
    }

    std::vector<int> state(n, -1);
    int current = x;
    long long cycle_length = 0;

    for (long long i = 0; i < rounds; ++i) {
        if (state[current] != -1) {
            cycle_length = i - state[current];
            break;
        }
        state[current] = i;
        current = (current + m) % n;
    }

    if (cycle_length > 0) {
        long long remaining_rounds = rounds - state[current];
        remaining_rounds %= cycle_length;
        for (long long i = 0; i < remaining_rounds; ++i) {
            current = (current + m) % n;
        }
    }

    std::cout << current << std::endl;
    return 0;
}