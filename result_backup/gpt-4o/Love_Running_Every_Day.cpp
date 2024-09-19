#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

struct Node {
    int time;
    vector<int> neighbors;
};

void bfs_distance(vector<Node>& nodes, vector<vector<int>>& dist, int start) {
    queue<int> q;
    q.push(start);
    vector<int> visited(nodes.size(), 0);
    visited[start] = 1;
    dist[start][start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (auto neighbor : nodes[current].neighbors) {
            if (!visited[neighbor]) {
                dist[start][neighbor] = dist[start][current] + 1;
                visited[neighbor] = 1;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Node> nodes(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        nodes[u].neighbors.push_back(v);
        nodes[v].neighbors.push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> nodes[i].time;
    }

    vector<pair<int, int>> players(m);
    for (int i = 0; i < m; ++i) {
        cin >> players[i].first >> players[i].second;
    }

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));

    for (int i = 1; i <= n; ++i) {
        bfs_distance(nodes, dist, i);
    }

    vector<int> result(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int s = players[i].first, t = players[i].second;
        int distance = dist[s][t];
        if (nodes[t].time == distance) {
            ++result[t];
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << result[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}