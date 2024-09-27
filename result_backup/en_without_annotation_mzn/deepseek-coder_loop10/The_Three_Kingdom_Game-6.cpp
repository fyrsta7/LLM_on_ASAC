#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int N;
vector<vector<int>> value;
vector<int> my_tactic;
vector<int> oppo_tactic;

int find_max(const vector<int>& my_set, const vector<int>& free_set) {
    int max_val = -1;
    int free_pointer = -1;
    for (int my_pointer : my_set) {
        for (int free_p : free_set) {
            if (value[my_pointer][free_p] > max_val) {
                max_val = value[my_pointer][free_p];
                free_pointer = free_p;
            }
        }
    }
    return free_pointer;
}

int find_value(const vector<int>& tactic) {
    int min_val = numeric_limits<int>::max();
    for (int i : tactic) {
        for (int j : tactic) {
            min_val = min(min_val, value[i][j]);
        }
    }
    return min_val;
}

void solve() {
    my_tactic.resize(N / 2);
    oppo_tactic.resize(N / 2);
    iota(my_tactic.begin(), my_tactic.end(), 1);

    for (int i = 0; i < N / 2; ++i) {
        vector<int> free_set(N);
        iota(free_set.begin(), free_set.end(), 1);
        for (int j = 0; j < i; ++j) {
            free_set.erase(remove(free_set.begin(), free_set.end(), my_tactic[j]), free_set.end());
            free_set.erase(remove(free_set.begin(), free_set.end(), oppo_tactic[j]), free_set.end());
        }
        oppo_tactic[i] = find_max(my_tactic, free_set);
    }

    int my_value = find_value(my_tactic);
    int oppo_value = find_value(oppo_tactic);

    if (my_value - oppo_value > 0) {
        cout << "1\n" << my_value << endl;
    } else {
        cout << "0" << endl;
    }
}

int main() {
    cin >> N;
    value.assign(N + 1, vector<int>(N + 1));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> value[i][j];
        }
    }
    solve();
    return 0;
}
