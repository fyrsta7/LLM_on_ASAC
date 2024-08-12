#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> magicValues(m);
    for (int i = 0; i < m; ++i) {
        cin >> magicValues[i];
    }

    vector<vector<int>> count(n + 1, vector<int>(4, 0));
    vector<int> freq(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        freq[magicValues[i]]++;
    }

    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            for (int c = b + 1; c <= n; ++c) {
                for (int d = c + 1; d <= n; ++d) {
                    if (b - a == 2 * (d - c) && b - a < (c - b) / 3) {
                        count[a][0] += freq[b] * freq[c] * freq[d];
                        count[b][1] += freq[a] * freq[c] * freq[d];
                        count[c][2] += freq[a] * freq[b] * freq[d];
                        count[d][3] += freq[a] * freq[b] * freq[c];
                    }
                }
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << count[magicValues[i]][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
