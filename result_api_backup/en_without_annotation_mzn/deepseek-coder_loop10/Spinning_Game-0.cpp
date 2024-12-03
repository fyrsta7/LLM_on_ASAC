#include <iostream>
#include <cmath>

int main() {
    int n, m, k, x;
    std::cin >> n >> m >> k >> x;

    int rounds = std::pow(10, k);
    int cycle_length = 0;
    int current_state = x;
    int states[n];

    for (int i = 0; i < n; ++i) {
        states[i] = -1;
    }

    for (int i = 0; i <= rounds; ++i) {
        if (states[current_state] != -1) {
            cycle_length = i - states[current_state];
            break;
        }
        states[current_state] = i;
        current_state = (current_state + m) % n;
    }

    if (cycle_length > 0) {
        int remaining_rounds = rounds % cycle_length;
        for (int i = 0; i < remaining_rounds; ++i) {
            current_state = (current_state + m) % n;
        }
    }

    std::cout << current_state << std::endl;
    return 0;
}