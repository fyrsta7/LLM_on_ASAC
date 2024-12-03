#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int N;
vector<vector<int>> value;

int find_value(const vector<int>& tactic) {
    int rtn = numeric_limits<int>::min();
    for (int i : tactic) {
        for (int j : tactic) {
            rtn = max(rtn, value[i - 1][j - 1]);
        }
    }
    return rtn;
}

int find_max(const vector<int>& my_set, const vector<int>& free_set) {
    int max_val = numeric_limits<int>::min();
    int max_index = -1;
    for (int i : my_set) {
        for (int j : free_set) {
            if (value[i - 1][j - 1] > max_val) {
                max_val = value[i - 1][j - 1];
                max_index = j;
            }
        }
    }
    return max_index;
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
    iota(full_set.begin(), full_set.end(), 1);
    
    int oppo_value = 0, my_value = 0;

    do {
        vector<int> my_set(my_tactic.begin(), my_tactic.begin() + N / 2);
        vector<int> free_set;
        
        for (int i = 1; i <= N; ++i) {
            if (find(my_tactic.begin(), my_tactic.begin() + N / 2, i) == my_tactic.begin() + N / 2) {
                free_set.push_back(i);
            }
        }
        
        for (int i = 0; i < N / 2; ++i) {
            oppo_tactic[i] = find_max(vector<int>(my_tactic.begin(), my_tactic.begin() + i + 1), free_set);
            free_set.erase(remove(free_set.begin(), free_set.end(), oppo_tactic[i]), free_set.end());
        }

        my_value = find_value(my_tactic);
        oppo_value = find_value(oppo_tactic);
        
    } while (next_permutation(my_tactic.begin(), my_tactic.begin() + N / 2));

    int answer;
    if (my_value - oppo_value > 0) {
        cout << "1\n" << my_value << "\n";
    } else {
        cout << "0\n";
    }

    return 0;
}