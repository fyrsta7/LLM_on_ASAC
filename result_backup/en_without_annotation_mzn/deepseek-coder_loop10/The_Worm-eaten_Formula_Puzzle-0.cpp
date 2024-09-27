#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool is_valid(const vector<vector<int>>& add_num, const vector<int>& result, int N) {
    int carry = 0;
    for (int i = N - 1; i >= 0; --i) {
        int sum = result[add_num[0][i]] + result[add_num[1][i]] + carry;
        if (sum % N != result[add_num[2][i]]) return false;
        carry = sum / N;
    }
    return true;
}

bool backtrack(vector<vector<int>>& add_num, vector<int>& result, vector<bool>& used, int N, int pos) {
    if (pos == N) return is_valid(add_num, result, N);

    for (int i = 0; i < N; ++i) {
        if (used[i]) continue;
        result[pos] = i;
        used[i] = true;
        if (backtrack(add_num, result, used, N, pos + 1)) return true;
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

    vector<vector<int>> add_num(3, vector<int>(N));
    unordered_map<string, int> char_to_index;
    for (int i = 0; i < N; ++i) {
        char_to_index[string(1, 'A' + i)] = i;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            add_num[i][j] = char_to_index[add[i][j]];
        }
    }

    vector<int> result(N, 0);
    vector<bool> used(N, false);
    backtrack(add_num, result, used, N, 0);

    for (int i = 0; i < N; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}