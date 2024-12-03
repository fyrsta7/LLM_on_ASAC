#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

vector<vector<Edge>> graph;
vector<int> army, camp, time;
vector<bool> city;
int n, m, max_time = INF;

void dijkstra(int start, vector<int>& dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist.assign(n + 1, INF);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& e : graph[u]) {
            int v = e.to;
            int w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void solve() {
    vector<int> dist_from_1(n + 1);
    dijkstra(1, dist_from_1);

    for (int i = 0; i < m; ++i) {
        vector<int> dist_from_army(n + 1);
        dijkstra(army[i], dist_from_army);
        time[i] = INF;
        for (int j = 0; j < m; ++j) {
            time[i] = min(time[i], dist_from_army[camp[j]]);
        }
    }

    max_time = *max_element(time.begin(), time.end());
}

int main() {
    cin >> n;
    graph.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    cin >> m;
    army.resize(m);
    camp.resize(m);
    time.resize(m);
    city.assign(n + 1, false);

    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> camp[i];
        city[camp[i]] = true;
    }

    solve();

    cout << max_time << endl;

    return 0;
}
