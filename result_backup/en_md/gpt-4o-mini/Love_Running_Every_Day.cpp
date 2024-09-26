#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> tree;
vector<int> w, res, dist_from_start, dist_from_end;

void bfs(int start, vector<int>& dist) {
    queue<int> q;
    vector<bool> visited(tree.size(), false);
    dist[start] = 0;
    visited[start] = true;
    q.push(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : tree[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    tree.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    
    w.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    
    res.resize(n + 1);
    vector<pair<int, int>> players(m);
    for (int i = 0; i < m; i++) {
        cin >> players[i].first >> players[i].second;
    }
    
    for (int i = 0; i < m; i++) {
        int s = players[i].first, t = players[i].second;
        
        // Perform BFS from the starting point
        dist_from_start.assign(n + 1, -1);
        bfs(s, dist_from_start);
        
        // Perform BFS from the endpoint
        dist_from_end.assign(n + 1, -1);
        bfs(t, dist_from_end);
        
        // Count observed players based on timing
        for (int j = 1; j <= n; j++) {
            if (dist_from_start[j] != -1 && dist_from_end[j] != -1) {
                int arrival_time = dist_from_start[j] + dist_from_end[j];
                if (arrival_time == w[j]) {
                    res[j]++;
                }
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
    
    return 0;
}