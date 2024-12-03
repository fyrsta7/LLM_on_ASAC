#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    
    vector<pair<int, int>> belt(m);
    for (int i = 0; i < m; ++i) {
        cin >> belt[i].first >> belt[i].second;
    }
    
    vector<pair<int, int>> order(q);
    int L = 0;
    for (int i = 0; i < q; ++i) {
        cin >> order[i].first >> order[i].second;
        L = max(L, order[i].second);
    }
    
    vector<vector<bool>> connected(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; ++i) {
        connected[belt[i].first][belt[i].second] = true;
        connected[belt[i].second][belt[i].first] = true;
    }
    
    vector<vector<int>> produce(q, vector<int>(n + 1, 0));
    for (int i = 0; i < q; ++i) {
        produce[i][order[i].first] = order[i].second;
    }
    
    for (int l = 1; l <= L; ++l) {
        for (int i = 0; i < q; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (produce[i][j] == l) {
                    for (int k = 1; k <= n; ++k) {
                        if (connected[j][k] && produce[i][k] == l - 1) {
                            produce[i][k] = l;
                        }
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < q; ++i) {
        if (produce[i][1] > 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
