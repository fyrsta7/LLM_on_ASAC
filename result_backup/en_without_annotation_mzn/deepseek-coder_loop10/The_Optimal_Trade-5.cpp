#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Road {
    int dest;
    bool bidirectional;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) cin >> price[i];

    unordered_map<int, vector<Road>> graph;
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        graph[u].push_back({v, t == 2});
        if (t == 2) graph[v].push_back({u, true});
    }

    vector<int> dist(n + 1, INT_MAX);
    vector<int> min_price(n + 1, INT_MAX);
    vector<int> max_price(n + 1, INT_MIN);
    vector<int> parent(n + 1, -1);
    dist[1] = 0;
    min_price[1] = price[1];

    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    pq.push({1, 0});

    while (!pq.empty()) {
        int u = pq.top().first;
        int d = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& road : graph[u]) {
            int v = road.dest;
            int new_dist = d + 1;
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                min_price[v] = min(min_price[u], price[v]);
                max_price[v] = max(max_price[u], price[v]);
                parent[v] = u;
                pq.push({v, new_dist});
            } else if (new_dist == dist[v]) {
                int new_min_price = min(min_price[u], price[v]);
                int new_max_price = max(max_price[u], price[v]);
                if (new_min_price < min_price[v] || new_max_price > max_price[v]) {
                    min_price[v] = new_min_price;
                    max_price[v] = new_max_price;
                    parent[v] = u;
                    pq.push({v, new_dist});
                }
            }
        }
    }

    int income = max_price[n] - min_price[n];
    cout << max(0, income) << endl;

    return 0;
}
