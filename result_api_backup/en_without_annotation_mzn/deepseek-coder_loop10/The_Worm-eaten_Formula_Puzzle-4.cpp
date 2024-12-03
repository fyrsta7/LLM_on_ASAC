#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool calculate(const vector<vector<int>>& cal, int i, int flag) {
    if (i == 0) return true;
    return ((cal[0][i] + cal[1][i] + flag) % cal.size() == cal[2][i]) &&
           calculate(cal, i - 1, (cal[0][i] + cal[1][i] + flag) / cal.size());
}

bool solve(vector<int>& result, vector<vector<int>>& add_num, int idx) {
    if (idx == result.size()) {
        vector<vector<int>> tmp(3, vector<int>(result.size()));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < result.size(); ++j) {
                tmp[i][j] = result[add_num[i][j]];
            }
        }
        return calculate(tmp, result.size() - 1, 0);
    }

    for (int i = 0; i < result.size(); ++i) {
        if (find(result.begin(), result.begin() + idx, i) == result.begin() + idx) {
            result[idx] = i;
            if (solve(result, add_num, idx + 1)) return true;
        }
    }
    return false;
}

int main() {
    int N;
    cin >> N;
    vector<vector<string>> add(3, vector<string>(N));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> add[i][j];
        }
    }

    vector<string> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    unordered_map<string, int> char_to_idx;
    for (int i = 0; i < N; ++i) {
        char_to_idx[alphabet[i]] = i;
    }

    vector<vector<int>> add_num(3, vector<int>(N));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            add_num[i][j] = char_to_idx[add[i][j]];
        }
    }

    vector<int> result(N);
    solve(result, add_num, 0);

    for (int i = 0; i < N; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
