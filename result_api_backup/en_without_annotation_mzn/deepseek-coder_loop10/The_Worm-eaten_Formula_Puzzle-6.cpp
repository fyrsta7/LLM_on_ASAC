#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool is_valid(vector<vector<int>>& add_num, vector<int>& result, int N) {
    int carry = 0;
    for (int i = N - 1; i >= 0; --i) {
        int sum = result[add_num[0][i]] + result[add_num[1][i]] + carry;
        if (sum % N != result[add_num[2][i]]) return false;
        carry = sum / N;
    }
    return true;
}

bool backtrack(vector<vector<int>>& add_num, vector<int>& result, vector<bool>& used, int idx, int N) {
    if (idx == N) return is_valid(add_num, result, N);

    for (int i = 0; i < N; ++i) {
        if (used[i]) continue;
        result[idx] = i;
        used[i] = true;
        if (backtrack(add_num, result, used, idx + 1, N)) return true;
        used[i] = false;
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

    unordered_map<string, int> char_to_idx;
    for (int i = 0; i < N; ++i) {
        char_to_idx[string(1, 'A' + i)] = i;
    }

    vector<vector<int>> add_num(3, vector<int>(N));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            add_num[i][j] = char_to_idx[add[i][j]];
        }
    }

    vector<int> result(N, -1);
    vector<bool> used(N, false);

    if (backtrack(add_num, result, used, 0, N)) {
        for (int i = 0; i < N; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No solution found" << endl;
    }

    return 0;
}