#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int cal_score(const vector<int>& row, const vector<bool>& actions) {
    int m = row.size();
    int head_count = 0;
    int tail_count = 0;
    int score = 0;
    for (int i = 0; i < m; ++i) {
        if (actions[i]) {
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
        vector<bool> actions(m);
        for (int j = 0; j < m; ++j) {
            actions[j] = (number[i][j] > number[i][m - 1 - j]);
        }
        total_score += cal_score(number[i], actions);
    }

    cout << total_score << endl;
    return 0;
}
