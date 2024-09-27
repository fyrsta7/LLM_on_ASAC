#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, k, x;
    cin >> n >> m >> k >> x;

    int rounds = 1;
    for (int i = 0; i < k; ++i) {
        rounds *= 10;
    }

    vector<int> state(n, -1);
    int current = x;
    int cycle_start = -1;

    for (int i = 0; i <= rounds; ++i) {
        if (state[current] != -1) {
            cycle_start = state[current];
            break;
        }
        state[current] = i;
        current = (current + m) % n;
    }

    if (cycle_start != -1) {
        int cycle_length = state.size() - cycle_start;
        int remaining_rounds = (rounds - cycle_start) % cycle_length;
        for (int i = 0; i < remaining_rounds; ++i) {
            current = (current + m) % n;
        }
    }

    cout << current << endl;
    return 0;
}