#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int N;
vector<vector<string>> add;
vector<int> result;
unordered_map<string, int> char_to_index;

bool is_valid(vector<int>& perm) {
    vector<vector<int>> tmp(3, vector<int>(N));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            tmp[i][j] = perm[char_to_index[add[i][j]]];
        }
    }

    int carry = 0;
    for (int i = N - 1; i >= 0; --i) {
        int sum = tmp[1][i] + tmp[2][i] + carry;
        if (sum % N != tmp[0][i]) return false;
        carry = sum / N;
    }
    return carry == 0;
}

int main() {
    cin >> N;
    add.resize(3, vector<string>(N));
    result.resize(N);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> add[i][j];
            if (char_to_index.find(add[i][j]) == char_to_index.end()) {
                char_to_index[add[i][j]] = char_to_index.size();
            }
        }
    }

    vector<int> perm(N);
    for (int i = 0; i < N; ++i) perm[i] = i;

    do {
        if (is_valid(perm)) {
            for (int i = 0; i < N; ++i) {
                result[char_to_index[add[0][i]]] = perm[i];
            }
            for (int i = 0; i < N; ++i) {
                cout << result[i] << " ";
            }
            cout << endl;
            return 0;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    cout << "No solution found" << endl;
    return 0;
}
