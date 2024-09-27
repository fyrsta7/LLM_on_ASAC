#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

int N;
vector<vector<int>> value;
vector<int> my_tactic, oppo_tactic;

int find_max(const vector<int>& my_set, const vector<int>& free_set) {
    int max_val = INT_MIN;
    int free_pointer = -1;
    for (int j : my_set) {
        for (int k : free_set) {
            if (value[j-1][k-1] > max_val) {
                max_val = value[j-1][k-1];
                free_pointer = k;
            }
        }
    }
    return free_pointer;
}

int find_value(const vector<int>& tactic) {
    int rtn = INT_MIN;
    for (int i : tactic) {
        for (int j : tactic) {
            rtn = max(rtn, value[i-1][j-1]);
        }
    }
    return rtn;
}

int main() {
    cin >> N;
    value.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> value[i][j];
        }
    }

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

    return 0;
}
