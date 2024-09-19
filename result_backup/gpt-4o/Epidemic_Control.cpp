#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
};

vector<vector<Edge>> adjList;
vector<int> troops;
vector<int> minDist;

void bfs(int start) {
    queue<int> q;
    vector<bool> visited(adjList.size(), false);
    q.push(start);
    visited[start] = true;
    minDist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &edge : adjList[u]) {
            int v = edge.to;
            int newDist = minDist[u] + edge.weight;
            if (!visited[v] || newDist < minDist[v]) {
                visited[v] = true;
                minDist[v] = newDist;
                q.push(v);
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    adjList.resize(n + 1);
    minDist.assign(n + 1, INT_MAX);

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    int m;
    cin >> m;

    troops.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> troops[i];
    }

    for (int troop : troops) {
        bfs(troop);
    }

    int maxDist = 0;
    bool possible = false;
    for (int i = 2; i <= n; ++i) {
        if (adjList[i].size() == 1) { // leaf node
            if (minDist[i] == INT_MAX) {
                cout << -1 << endl;
                return 0;
            }
            maxDist = max(maxDist, minDist[i]);
            possible = true;
        }
    }

    cout << (possible ? maxDist : -1) << endl;

    return 0;
}