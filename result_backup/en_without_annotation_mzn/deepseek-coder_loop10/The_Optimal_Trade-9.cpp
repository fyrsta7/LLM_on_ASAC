#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }
    vector<vector<pair<int, int>>> roads(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        roads[u].emplace_back(v, t);
        roads[v].emplace_back(u, t);
    }

    vector<int> min_price(n + 1, INT_MAX);
    vector<int> max_price(n + 1, INT_MIN);
    vector<bool> visited(n + 1, false);

    min_price[1] = price[1];
    max_price[1] = price[1];

    for (int step = 0; step < n; ++step) {
        int u = -1;
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && (u == -1 || min_price[i] < min_price[u])) {
                u = i;
            }
        }
        visited[u] = true;
        for (auto& road : roads[u]) {
            int v = road.first;
            int t = road.second;
            if (t == 1) {
                min_price[v] = min(min_price[v], min_price[u]);
                max_price[v] = max(max_price[v], max_price[u]);
            } else {
                min_price[v] = min(min_price[v], max_price[u]);
                max_price[v] = max(max_price[v], min_price[u]);
            }
        }
    }

    int income = max_price[n] - min_price[n];
    cout << max(0, income) << endl;

    return 0;
}