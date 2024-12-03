#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

struct Road {
    int u, v;
};

struct Player {
    int start, end;
};

vector<int> watcher;
vector<Road> road;
vector<Player> player;
vector<vector<int>> adj;
vector<int> time_taken;

void bfs(int start, int end, int player_idx) {
    vector<int> dist(adj.size(), INT_MAX);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == end) {
            time_taken[player_idx] = dist[u];
            return;
        }

        for (int v : adj[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    road.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> road[i].u >> road[i].v;
    }

    watcher.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> watcher[i];
    }

    player.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> player[i].start >> player[i].end;
    }

    adj.resize(n + 1);
    for (const auto& r : road) {
        adj[r.u].push_back(r.v);
        adj[r.v].push_back(r.u);
    }

    time_taken.resize(m, INT_MAX);
    for (int i = 0; i < m; ++i) {
        bfs(player[i].start, player[i].end, i);
    }

    vector<int> watch_num(n, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (watcher[j] <= time_taken[i]) {
                int loc = player[i].end;
                if (time_taken[i] >= watcher[j]) {
                    watch_num[j]++;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << watch_num[i] << " ";
    }
    cout << endl;

    return 0;
}
