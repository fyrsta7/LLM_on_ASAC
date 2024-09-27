#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int N;
vector<vector<int>> value;

int find_max(const vector<int>& my_set, const vector<int>& free_set) {
    int max_val = INT_MIN;
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
    int min_val = INT_MAX;
    for (int i : tactic) {
        for (int j : tactic) {
            min_val = min(min_val, value[i][j]);
        }
    }
    return min_val;
}

int main() {
    cin >> N;
    value.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> value[i][j];
        }
    }

    vector<int> my_tactic(N / 2);
    vector<int> oppo_tactic(N / 2);
    vector<int> full_set(N);
    iota(full_set.begin(), full_set.end(), 0);

    for (int i = 0; i < N / 2; ++i) {
        vector<int> my_set(my_tactic.begin(), my_tactic.begin() + i);
        vector<int> free_set = full_set;
        for (int j = 0; j < i; ++j) {
            free_set.erase(remove(free_set.begin(), free_set.end(), my_tactic[j]), free_set.end());
            free_set.erase(remove(free_set.begin(), free_set.end(), oppo_tactic[j]), free_set.end());
        }
        oppo_tactic[i] = find_max(my_set, free_set);
        free_set.erase(remove(free_set.begin(), free_set.end(), oppo_tactic[i]), free_set.end());
        my_tactic[i] = find_max(my_set, free_set);
    }

    int my_value = find_value(my_tactic);
    int oppo_value = find_value(oppo_tactic);

    if (my_value > oppo_value) {
        cout << "1\n" << my_value << endl;
    } else {
        cout << "0" << endl;
    }

    return 0;
}
