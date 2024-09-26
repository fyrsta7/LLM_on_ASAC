#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int cal_score(const vector<int>& row, const vector<bool>& actions) {
    int m = row.size();
    vector<int> heads, tails;
    for (int i = 0; i < m; ++i) {
        if (actions[i]) {
            heads.push_back(row[i]);
        } else {
            tails.push_back(row[i]);
        }
    }
    int score = 0;
    int head_index = 0, tail_index = m - 1;
    for (int i = 0; i < m; ++i) {
        if (actions[i]) {
            score += pow(2, i) * heads[head_index++];
        } else {
            score += pow(2, i) * tails[tail_index--];
        }
    }
    return score;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> number(n, vector<int>(m));
    vector<vector<bool>> take_number(n, vector<bool>(m, false));

    // Input numbers array
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> number[i][j];
        }
    }

    int total_score = 0;

    // Greedily decide choices
    for (int i = 0; i < n; ++i) {
        vector<int> row = number[i];
        sort(row.begin(), row.end());

        int head_matches = 0, tail_matches = 0;
        vector<bool> choice(m, false);

        for (int j = 0; j < m; ++j) {
            if (row[j] >= row[m - 1 - j]) {
                choice[j] = true; // Take as head
                ++head_matches;
            } else {
                choice[m - 1 - j] = true; // Take as tail
                ++tail_matches;
            }
        }

        total_score += cal_score(row, choice);
    }

    cout << total_score << endl;

    return 0;
}