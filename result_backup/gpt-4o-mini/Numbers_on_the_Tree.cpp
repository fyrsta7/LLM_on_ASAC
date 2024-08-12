#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> position(n + 1), parent(n + 1);
    
    for (int i = 1; i <= n; ++i) {
        cin >> position[i];
    }
    
    vector<vector<int>> tree(n + 1);
    
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    
    vector<int> result(n + 1);
    for (int i = 1; i <= n; ++i) {
        result[position[i]] = i;
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int a, int b) {
        return result[a] < result[b];
    });
    
    vector<int> final_position(n + 1);
    for (int i = 0; i < n; ++i) {
        final_position[i + 1] = order[i];
    }
    
    for (int i = 1; i <= n; ++i) {
        cout << final_position[i] << " ";
    }
    cout << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}