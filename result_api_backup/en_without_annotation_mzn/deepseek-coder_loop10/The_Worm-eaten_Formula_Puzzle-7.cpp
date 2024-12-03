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

bool is_valid(int idx, int value) {
    if (result[idx] != -1) return false;
    for (int i = 0; i < N; ++i) {
        if (result[i] == value) return false;
    }
    return true;
}

bool calculate(int idx, int carry) {
    if (idx == -1) return carry == 0;

    int a = result[char_to_index[add[0][idx]]];
    int b = result[char_to_index[add[1][idx]]];
    int c = result[char_to_index[add[2][idx]]];

    if (a == -1 || b == -1 || c == -1) return false;

    return (a + b + carry) % N == c && calculate(idx - 1, (a + b + carry) / N);
}

bool solve(int idx) {
    if (idx == N) return calculate(N - 1, 0);

    for (int value = 0; value < N; ++value) {
        if (is_valid(idx, value)) {
            result[idx] = value;
            if (solve(idx + 1)) return true;
            result[idx] = -1;
        }
    }
    return false;
}

int main() {
    cin >> N;
    add.resize(3, vector<string>(N));
    result.assign(N, -1);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> add[i][j];
            if (char_to_index.find(add[i][j]) == char_to_index.end()) {
                char_to_index[add[i][j]] = char_to_index.size();
            }
        }
    }

    if (solve(0)) {
        for (int i = 0; i < N; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}
