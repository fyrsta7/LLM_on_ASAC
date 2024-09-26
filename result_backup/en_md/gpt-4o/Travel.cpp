#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<int> adj[5001];
bool visited[5001];
vector<int> result;

void dfs(int v) {
    visited[v] = true;
    result.push_back(v);
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u);
            result.push_back(v);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        sort(adj[i].begin(), adj[i].end());
    }
    dfs(1);
    for (int i = 0; i < result.size(); ++i) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;
    return 0;
}