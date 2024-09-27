#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int to, id;
};

vector<vector<Edge>> graph;
vector<int> watcher, player, time_taken;
vector<vector<int>> route;
vector<vector<int>> location;
vector<int> watch_num;

void bfs(int start, int end, int player_id) {
    int n = graph.size();
    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &e : graph[u]) {
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
        for (auto &e : graph[current]) {
            if (e.to == parent[current]) {
                path.push_back(e.id);
                break;
            }
        }
        current = parent[current];
    }
    reverse(path.begin(), path.end());

    time_taken[player_id] = path.size();
    route[player_id] = path;
    location[player_id][0] = start;
    for (int i = 0; i < path.size(); i++) {
        int road_id = path[i];
        int from = graph[road_id][0].to;
        int to = graph[road_id][1].to;
        location[player_id][i + 1] = to;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    watcher.resize(n + 1);
    player.resize(m, vector<int>(2));
    time_taken.resize(m);
    route.resize(m, vector<int>(n - 1));
    location.resize(m, vector<int>(n));
    watch_num.resize(n + 1);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
    }

    for (int i = 1; i <= n; i++) {
        cin >> watcher[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> player[i][0] >> player[i][1];
        bfs(player[i][0], player[i][1], i);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (time_taken[j] >= watcher[i] && location[j][watcher[i]] == i) {
                watch_num[i]++;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << watch_num[i] << " ";
    }
    cout << endl;

    return 0;
}
