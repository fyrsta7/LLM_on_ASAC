#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Road {
    int u, v;
};

struct Player {
    int start, end;
};

int n, m;
vector<Road> roads;
vector<int> watcher;
vector<Player> players;

vector<int> dijkstra(int start, int end) {
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& road : roads) {
            if (road.u == u || road.v == u) {
                int v = (road.u == u) ? road.v : road.u;
                if (dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    return dist;
}

int main() {
    cin >> n >> m;
    roads.resize(n - 1);
    watcher.resize(n);
    players.resize(m);

    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v;
    }

    for (int i = 0; i < n; ++i) {
        cin >> watcher[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> players[i].start >> players[i].end;
    }

    vector<int> watch_num(n, 0);

    for (int i = 0; i < m; ++i) {
        vector<int> dist = dijkstra(players[i].start, players[i].end);
        int time = dist[players[i].end];
        for (int j = 0; j < n; ++j) {
            if (dist[j] <= watcher[j]) {
                watch_num[j]++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << watch_num[i] << " ";
    }
    cout << endl;

    return 0;
}
