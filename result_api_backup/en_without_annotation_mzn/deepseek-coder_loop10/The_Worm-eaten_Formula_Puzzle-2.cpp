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

bool is_valid(int idx, int carry) {
    if (idx < 0) return carry == 0;
    int a = result[char_to_index[add[0][idx]]];
    int b = result[char_to_index[add[1][idx]]];
    int c = result[char_to_index[add[2][idx]]];
    return (a + b + carry) % N == c && is_valid(idx - 1, (a + b + carry) / N);
}

bool backtrack(int pos) {
    if (pos == N) return is_valid(N - 1, 0);
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
            if (!char_to_index.count(add[i][j])) {
                char_to_index[add[i][j]] = char_to_index.size();
            }
        }
    }
    backtrack(0);
    for (int i = 0; i < N; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}
