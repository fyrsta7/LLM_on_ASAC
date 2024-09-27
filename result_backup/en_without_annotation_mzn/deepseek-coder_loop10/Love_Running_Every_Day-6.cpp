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

vector<int> dijkstra(int start) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Road& road : roads) {
            if (road.u == u || road.v == u) {
                int v = (road.u == u) ? road.v : road.u;
                int newDist = d + 1;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    pq.push({newDist, v});
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

    vector<vector<int>> watch_num(n, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        vector<int> distStart = dijkstra(players[i].start);
        vector<int> distEnd = dijkstra(players[i].end);

        for (int j = 0; j < n; ++j) {
            if (distStart[j] + distEnd[j] == distStart[players[i].end]) {
                for (int k = 0; k < watcher[j]; ++k) {
                    watch_num[j][k]++;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << watch_num[i][watcher[i]] << " ";
    }
    cout << endl;

    return 0;
}