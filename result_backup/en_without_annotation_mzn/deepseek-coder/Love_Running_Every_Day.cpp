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

int main() {
    int n, m;
    cin >> n >> m;

    vector<Road> roads(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v;
    }

    vector<int> watcher(n);
    for (int i = 0; i < n; ++i) {
        cin >> watcher[i];
    }

    vector<Player> players(m);
    for (int i = 0; i < m; ++i) {
        cin >> players[i].start >> players[i].end;
    }

    vector<vector<int>> adj(n + 1);
    for (const auto& road : roads) {
        adj[road.u].push_back(road.v);
        adj[road.v].push_back(road.u);
    }

    vector<int> watch_num(n, 0);

    for (const auto& player : players) {
        vector<int> dist(n + 1, -1);
        queue<int> q;
        q.push(player.start);
        dist[player.start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (dist[player.end] >= watcher[i] && dist[i + 1] == watcher[i]) {
                watch_num[i]++;
            }
        }
    }

    for (int num : watch_num) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
