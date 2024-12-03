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
    
    for (int l = 1; l <= L; ++l) {
        vector<vector<int>> new_produce = produce;
        for (const auto& b : belt) {
            int u = b.first - 1, v = b.second - 1;
            for (int i = 0; i < q; ++i) {
                if (produce[i][u] == 1) {
                    new_produce[i][v] = 1;
                }
                if (produce[i][v] == 1) {
                    new_produce[i][u] = 1;
                }
            }
        }
        produce = new_produce;
    }
    
    for (int i = 0; i < q; ++i) {
        if (produce[i][0] > 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
