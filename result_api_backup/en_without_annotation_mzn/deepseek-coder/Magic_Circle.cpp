#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> X(m);
    for (int i = 0; i < m; ++i) {
        cin >> X[i];
    }

    vector<vector<int>> ans(m, vector<int>(4, 0));
    int max_num = m * (m - 1) * (m - 2) * (m - 3) / 24;
    vector<vector<int>> magic(max_num, vector<int>(4));
    int num = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            for (int k = j + 1; k < m; ++k) {
                for (int l = k + 1; l < m; ++l) {
                    if (X[j] - X[i] == 2 * (X[l] - X[k]) && 3 * (X[j] - X[i]) < (X[k] - X[j])) {
                        magic[num][0] = i + 1;
                        magic[num][1] = j + 1;
                        magic[num][2] = k + 1;
                        magic[num][3] = l + 1;
                        ++num;
                    }
                }
            }
        }
    }

    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < 4; ++j) {
            ++ans[magic[i][j] - 1][j];
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << endl;
    }

    return 0;
}
