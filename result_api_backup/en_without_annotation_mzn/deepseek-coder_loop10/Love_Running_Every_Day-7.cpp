#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int to, id;
};

vector<vector<Edge>> adj;
vector<int> watcher, player1, player2;
vector<vector<int>> route;
vector<int> time;
vector<vector<int>> location;
vector<int> watch_num;

void bfs(int start, int player_id) {
    queue<pair<int, int>> q;
    q.push({start, 0});
    vector<bool> visited(adj.size(), false);
    visited[start] = true;
    while (!q.empty()) {
        auto [u, t] = q.front();
        q.pop();
        if (u == player2[player_id]) {
            time[player_id] = t;
            break;
        }
        for (auto &e : adj[u]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                route[player_id][t] = e.id;
                location[player_id][t] = u;
                q.push({e.to, t + 1});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    watcher.resize(n + 1);
    player1.resize(m);
    player2.resize(m);
    route.assign(m, vector<int>(n - 1));
    time.assign(m, 0);
    location.assign(m, vector<int>(n));
    watch_num.assign(n + 1, 0);

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    for (int i = 1; i <= n; ++i) {
        cin >> watcher[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> player1[i] >> player2[i];
        bfs(player1[i], i);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < time[i]; ++j) {
            if (j < watcher[location[i][j]]) {
                watch_num[location[i][j]]++;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << watch_num[i] << " ";
    }
    cout << endl;

    return 0;
}
