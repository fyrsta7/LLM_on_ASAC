#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
const int MAXN = 10000;
vector<pii> adj[MAXN + 1];
int maxWeight[MAXN + 1][MAXN + 1];

void dijkstra(int start, int n) {
    priority_queue<pii> pq;
    vector<int> dist(n + 1, -1);
    pq.push({1e9, start});
    dist[start] = 1e9;

    while (!pq.empty()) {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();

        if (w < dist[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int weight = min(edge.second, w);
            if (dist[v] < weight) {
                dist[v] = weight;
                pq.push({weight, v});
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        maxWeight[start][i] = dist[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
    }

    for (int i = 1; i <= n; ++i) {
        dijkstra(i, n);
    }

    int q;
    cin >> q;

    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << maxWeight[x][y] << '\n';
    }

    return 0;
}
