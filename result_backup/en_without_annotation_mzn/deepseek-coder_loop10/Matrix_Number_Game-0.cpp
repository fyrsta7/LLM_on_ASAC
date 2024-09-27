#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int cal_score(const vector<int>& row, const vector<int>& actions) {
    int m = row.size();
    int score = 0;
    int head_count = 0;
    int tail_count = 0;
    for (int i = 0; i < m; ++i) {
        if (actions[i] == 0) {
            score += pow(2, i + 1) * row[head_count];
            ++head_count;
        } else {
            score += pow(2, i + 1) * row[m - 1 - tail_count];
            ++tail_count;
        }
    }
    return score;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> number(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> number[i][j];
        }
    }

    int total_score = 0;
    for (int i = 0; i < n; ++i) {
        sort(number[i].begin(), number[i].end(), greater<int>());
        vector<int> actions(m);
        for (int j = 0; j < m; ++j) {
            actions[j] = (j < m / 2) ? 0 : 1;
        }
        sort(actions.begin(), actions.end());
        int max_score = 0;
        do {
            int score = cal_score(number[i], actions);
            if (score > max_score) {
                max_score = score;
            }
        } while (next_permutation(actions.begin(), actions.end()));
        total_score += max_score;
    }

    cout << total_score << endl;
    return 0;
}