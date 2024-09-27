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

    vector<int> dist(n + 1, INT_MAX);
    vector<int> buy(n + 1, INT_MAX);
    vector<int> sell(n + 1, INT_MIN);
    dist[1] = 0;
    buy[1] = price[1];

    for (int i = 1; i <= n; ++i) {
        for (int u = 1; u <= n; ++u) {
            if (dist[u] == INT_MAX) continue;
            for (auto& road : roads[u]) {
                int v = road.first;
                int t = road.second;
                if (t == 1 && dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    buy[v] = min(buy[u], price[v]);
                    sell[v] = max(sell[u], price[v]);
                } else if (t == 2 && dist[v] >= dist[u]) {
                    dist[v] = dist[u];
                    buy[v] = min(buy[u], price[v]);
                    sell[v] = max(sell[u], price[v]);
                }
            }
        }
    }

    int income = sell[n] - buy[n];
    cout << max(0, income) << endl;

    return 0;
}