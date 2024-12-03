#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int to, id;
};

vector<vector<Edge>> adj;
vector<int> watcher, player1, player2, time_taken;
vector<vector<int>> route;
vector<int> watch_num;

void bfs(int start, int end, int player_id) {
    int n = adj.size();
    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& e : adj[u]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + 1;
                parent[e.to] = u;
                q.push(e.to);
            }
        }
    }

    int current = end;
    vector<int> path;
    while (current != start) {
        int prev = parent[current];
        for (auto& e : adj[prev]) {
            if (e.to == current) {
                path.push_back(e.id);
                break;
            }
        }
        current = prev;
    }
    reverse(path.begin(), path.end());
    route[player_id] = path;
    time_taken[player_id] = dist[end];
}

int main() {
    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);
    watcher.resize(n + 1);
    player1.resize(m + 1);
    player2.resize(m + 1);
    time_taken.resize(m + 1);
    route.resize(m + 1);
    watch_num.resize(n + 1);

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    for (int i = 1; i <= n; ++i) {
        cin >> watcher[i];
    }

    for (int i = 1; i <= m; ++i) {
        cin >> player1[i] >> player2[i];
        bfs(player1[i], player2[i], i);
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < time_taken[i]; ++j) {
            int loc = (j < watcher[route[i][j]]) ? route[i][j] : route[i][j + 1];
            if (j >= watcher[loc]) {
                watch_num[loc]++;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << watch_num[i] << " ";
    }
    cout << endl;

    return 0;
}
