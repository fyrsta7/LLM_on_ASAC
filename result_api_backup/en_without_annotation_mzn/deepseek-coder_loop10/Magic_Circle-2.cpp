#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> X(m);
    for (int i = 0; i < m; ++i) cin >> X[i];

    vector<vector<int>> ans(m, vector<int>(4, 0));
    vector<vector<int>> magic;

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            for (int k = j + 1; k < m; ++k) {
                for (int l = k + 1; l < m; ++l) {
                    if (X[j] - X[i] == 2 * (X[l] - X[k]) && 3 * (X[j] - X[i]) < (X[k] - X[j])) {
                        magic.push_back({i + 1, j + 1, k + 1, l + 1});
                    }
                }
            }
        }
    }

    for (const auto& quad : magic) {
        for (int j = 0; j < 4; ++j) {
            ans[quad[j] - 1][j]++;
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << "\n";
    }

    return 0;
}
