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
    
    vector<vector<int>> produce(q, vector<int>(n, 0));
    for (int i = 0; i < q; ++i) {
        produce[i][order[i].first - 1] = 1;
    }
    
    vector<vector<bool>> connected(n, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        connected[belt[i].first - 1][belt[i].second - 1] = true;
        connected[belt[i].second - 1][belt[i].first - 1] = true;
    }
    
    for (int l = 1; l <= L; ++l) {
        for (int i = 0; i < q; ++i) {
            vector<int> new_produce(n, 0);
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (connected[j][k]) {
                        new_produce[j] |= produce[i][k];
                    }
                }
            }
            produce[i] = new_produce;
        }
    }
    
    for (int i = 0; i < q; ++i) {
        cout << (produce[i][0] ? "YES" : "NO") << endl;
    }
    
    return 0;
}
