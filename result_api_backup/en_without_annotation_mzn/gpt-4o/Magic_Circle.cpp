#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> X;
vector<vector<int>> ans;

bool isValid(vector<int>& seq) {
    return X[seq[1]] - X[seq[0]] == 2 * (X[seq[3]] - X[seq[2]]) &&
           3 * (X[seq[1]] - X[seq[0]]) < (X[seq[2]] - X[seq[1]]);
}

int main() {
    cin >> n >> m;
    X.resize(m);
    ans.resize(m, vector<int>(4, 0));

    for (int i = 0; i < m; ++i) {
        cin >> X[i];
    }

    int max_num = 0;
    vector<vector<int>> magic;

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            for (int k = j + 1; k < m; ++k) {
                for (int l = k + 1; l < m; ++l) {
                    vector<int> seq = {i, j, k, l};
                    if (isValid(seq)) {
                        magic.push_back(seq);
                        ++max_num;
                    }
                }
            }
        }
    }

    for (const auto& seq : magic) {
        for (int i = 0; i < 4; ++i) {
            ++ans[seq[i]][i];
        }
    }

    for (const auto& row : ans) {
        for (int x : row) {
            cout << x << " ";
        }
        cout << "\n";
    }

    return 0;
}