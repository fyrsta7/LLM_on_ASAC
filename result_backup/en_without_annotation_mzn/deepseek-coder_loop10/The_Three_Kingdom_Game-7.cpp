#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int N;
vector<vector<int>> value;
vector<int> my_tactic, oppo_tactic;
int oppo_value, my_value;

int find_max(const vector<int>& my_set, const vector<int>& free_set) {
    int max_val = -1, max_idx = -1;
    for (int i : my_set) {
        for (int j : free_set) {
            if (value[i][j] > max_val) {
                max_val = value[i][j];
                max_idx = j;
            }
        }
    }
    return max_idx;
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
    vector<int> full_set(N);
    iota(full_set.begin(), full_set.end(), 1);

    for (int i = 0; i < N / 2; ++i) {
        vector<int> my_set(my_tactic.begin(), my_tactic.begin() + i + 1);
        vector<int> free_set;
        set_difference(full_set.begin(), full_set.end(), my_set.begin(), my_set.end(), back_inserter(free_set));
        set_difference(free_set.begin(), free_set.end(), oppo_tactic.begin(), oppo_tactic.begin() + i, back_inserter(free_set));
        oppo_tactic[i] = find_max(my_set, free_set);
    }

    my_value = find_value(my_tactic);
    oppo_value = find_value(oppo_tactic);
}

int main() {
    cin >> N;
    value.resize(N, vector<int>(N));
    my_tactic.resize(N / 2);
    oppo_tactic.resize(N / 2);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> value[i][j];
        }
    }

    for (int i = 0; i < N / 2; ++i) {
        my_tactic[i] = i + 1;
    }

    solve();

    if (my_value - oppo_value > 0) {
        cout << "1\n" << my_value << endl;
    } else {
        cout << "0" << endl;
    }

    return 0;
}
