#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

bool check_need_raw_materials(int n, int a, int L) {
    if (L == 1) return adj[a].end() != find(adj[a].begin(), adj[a].end(), 1);

    queue<int> q;
    fill(visited.begin(), visited.end(), false);
    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int neighbor : adj[cur]) {
            if (neighbor == a) return true;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return false;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    adj.assign(n + 1, vector<int>());
    visited.assign(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < q; ++i) {
        int a, L;
        cin >> a >> L;
        if (check_need_raw_materials(n, a, L)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}