#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, k, x;
    cin >> n >> m >> k >> x;

    int rounds = 1;
    for (int i = 0; i < k; ++i) rounds *= 10;

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
        rounds = (rounds - cycle_start) % cycle_length + cycle_start;
    }

    for (int i = 0; i < n; ++i) {
        if (state[i] == rounds) {
            cout << i << endl;
            break;
        }
    }

    return 0;
}