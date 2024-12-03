#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

struct Road {
    int u, v;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Road> roads(m);
    for (int i = 0; i < m; ++i) {
        cin >> roads[i].u >> roads[i].v;
    }

    vector<vector<int>> adj(n + 1);
    for (const auto& road : roads) {
        adj[road.u].push_back(road.v);
        adj[road.v].push_back(road.u);
    }

    vector<int> route(2 * n, -1);
    vector<bool> visited(n + 1, false);
    vector<int> first(n + 1, -1);

    queue<int> q;
    q.push(1);
    visited[1] = true;
    route[0] = 1;
    first[1] = 1;

    int length = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                route[length++] = v;
                first[v] = length;
                q.push(v);
            }
        }
    }

    route[length] = 1;
    ++length;

    int score = 0;
    for (int i = 1; i <= n; ++i) {
        score += pow(n, n - i) * first[i];
    }

    cout << score << endl;

    return 0;
}
