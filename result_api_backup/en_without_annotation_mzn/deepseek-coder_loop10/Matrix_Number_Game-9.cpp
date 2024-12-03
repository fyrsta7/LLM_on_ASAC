#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int cal_score(const vector<int>& row, const vector<int>& actions) {
    int m = row.size();
    vector<int> heads, tails;
    for (int i = 0; i < m; ++i) {
        if (actions[i] == 0) heads.push_back(row[i]);
        else tails.push_back(row[i]);
    }
    reverse(tails.begin(), tails.end());
    vector<int> combined = heads;
    combined.insert(combined.end(), tails.begin(), tails.end());

    int score = 0;
    for (int i = 0; i < m; ++i) {
        score += pow(2, i + 1) * combined[i];
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
        vector<int> actions(m);
        for (int j = 0; j < m; ++j) {
            actions[j] = (j < m / 2) ? 0 : 1;
        }
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