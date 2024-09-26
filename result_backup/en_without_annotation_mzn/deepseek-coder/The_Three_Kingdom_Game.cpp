#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int N;
vector<vector<int>> value;
vector<int> my_tactic, oppo_tactic;

int find_max(const vector<int>& my_set, const vector<int>& free_set) {
    int max_val = -1, max_idx = -1;
    for (int i : my_set) {
        for (int j : free_set) {
            if (value[i-1][j-1] > max_val) {
                max_val = value[i-1][j-1];
                max_idx = j;
            }
        }
    }
    return max_idx;
}

int find_value(const vector<int>& tactic) {
    int min_val = INT32_MAX;
    for (int i : tactic) {
        for (int j : tactic) {
            min_val = min(min_val, value[i-1][j-1]);
        }
    }
    return min_val;
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

    return 0;
}
