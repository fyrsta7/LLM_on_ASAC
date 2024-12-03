#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> subtree;
vector<vector<set<int>>> subsubtree;
vector<vector<int>> center;

bool bfs(int start, int end, set<int> forbiddenEdges) {
    vector<bool> visited(adj.size(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (forbiddenEdges.find(neighbor) != forbiddenEdges.end()) continue;
            if (neighbor == end) return true;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return false;
}

bool isConnectedWithout(int a, int b, set<int> forbiddenEdges) {
    return bfs(a, b, forbiddenEdges);
}

bool isValidSubtree(int i, int j) {
    for (int k : subtree[i][j]) {
        for (int x : subsubtree[i][j][k]) {
            for (int y : subsubtree[i][j][k]) {
                if (x != y && !isConnectedWithout(x, y, {i})) return false;
            }
        }
    }
    return true;
}

bool isValidTree() {
    for (int i = 0; i < adj.size() - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!isValidSubtree(i, j)) return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;

    adj.resize(n + 1);
    subtree.resize(n, vector<int>(2));
    subsubtree.resize(n, vector<set<int>>(2, set<int>(n)));
    center.resize(n, vector<int>(2));

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Initialize subtree and subsubtree structures
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            subtree[i][j] = {1, 2, 3, ..., n}; // Example initialization
            for (int k = 0; k < n; ++k) {
                subsubtree[i][j][k] = {1, 2, 3, ..., n}; // Example initialization
            }
        }
    }

    if (isValidTree()) {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < 2; ++j) {
                cout << center[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}
