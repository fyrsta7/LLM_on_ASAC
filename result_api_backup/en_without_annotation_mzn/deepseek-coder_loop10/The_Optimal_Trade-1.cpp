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
    vector<int> min_price(n + 1, INT_MAX);
    vector<int> max_price(n + 1, INT_MIN);
    vector<bool> visited(n + 1, false);

    dist[1] = 0;
    min_price[1] = price[1];
    max_price[1] = price[1];

    for (int i = 1; i <= n; ++i) {
        int u = -1;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = true;

        for (auto& road : roads[u]) {
            int v = road.first;
            int t = road.second;
            if (visited[v]) continue;
            int new_dist = dist[u] + 1;
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                min_price[v] = min(min_price[u], price[v]);
                max_price[v] = max(max_price[u], price[v]);
            } else if (new_dist == dist[v]) {
                min_price[v] = min(min_price[v], min(min_price[u], price[v]));
                max_price[v] = max(max_price[v], max(max_price[u], price[v]));
            }
        }
    }

    int income = max_price[n] - min_price[n];
    cout << max(0, income) << endl;

    return 0;
}