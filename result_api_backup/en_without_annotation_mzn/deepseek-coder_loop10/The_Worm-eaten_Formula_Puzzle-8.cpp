#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int N;
vector<vector<string>> add;
unordered_map<string, int> char_to_index;
vector<int> result;

bool is_valid(vector<vector<int>>& add_num, vector<int>& result) {
    vector<vector<int>> tmp(3, vector<int>(N));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            tmp[i][j] = result[add_num[i][j]];
        }
    }

    int flag = 0;
    for (int i = N - 1; i >= 0; --i) {
        int sum = tmp[1][i] + tmp[2][i] + flag;
        if (sum % N != tmp[3][i]) return false;
        flag = sum / N;
    }
    return flag == 0;
}

bool backtrack(int pos) {
    if (pos == N) {
        return is_valid(add, result);
    }

    for (int i = 0; i < N; ++i) {
        if (find(result.begin(), result.begin() + pos, i) == result.begin() + pos) {
            result[pos] = i;
            if (backtrack(pos + 1)) return true;
        }
    }
    return false;
}

int main() {
    cin >> N;
    add.resize(3, vector<string>(N));
    result.resize(N);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> add[i][j];
            if (i == 0) char_to_index[add[i][j]] = j;
        }
    }

    if (backtrack(0)) {
        for (int i = 0; i < N; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No solution found" << endl;
    }

    return 0;
}