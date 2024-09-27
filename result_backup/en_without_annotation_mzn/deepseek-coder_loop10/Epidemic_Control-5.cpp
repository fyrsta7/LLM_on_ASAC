#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> adj;
vector<int> army, camp, time_to_camp;
vector<bool> is_leaf, visited;

void bfs(int start, vector<int>& dist) {
    fill(visited.begin(), visited.end(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + w;
                q.push(v);
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    adj.resize(n + 1);
    army.resize(n - 1);
    camp.resize(n - 1);
    time_to_camp.resize(n - 1);
    is_leaf.resize(n + 1, true);
    visited.resize(n + 1, false);

    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
        is_leaf[u] = is_leaf[v] = false;
    }

    int m;
    cin >> m;
    army.resize(m);
    camp.resize(m);
    time_to_camp.resize(m);

    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> camp[i];
    }

    vector<int> dist_from_1(n + 1, numeric_limits<int>::max());
    bfs(1, dist_from_1);

    for (int i = 0; i < m; ++i) {
        vector<int> dist_from_army(n + 1, numeric_limits<int>::max());
        bfs(army[i], dist_from_army);
        time_to_camp[i] = dist_from_army[camp[i]];
    }

    int max_time = *max_element(time_to_camp.begin(), time_to_camp.end());
    cout << max_time << endl;

    return 0;
}
