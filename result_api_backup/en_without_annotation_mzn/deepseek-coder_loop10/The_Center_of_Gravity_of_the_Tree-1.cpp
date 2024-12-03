#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct Edge {
    int u, v;
};

vector<vector<int>> adj;
vector<Edge> edges;
vector<vector<set<int>>> subtree;
vector<vector<int>> center;
int n;

bool bfs(int start, int end, set<int>& forbiddenEdges) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            int edgeIndex = -1;
            for (int i = 0; i < edges.size(); ++i) {
                if ((edges[i].u == node && edges[i].v == neighbor) || (edges[i].u == neighbor && edges[i].v == node)) {
                    edgeIndex = i;
                    break;
                }
            }
            if (forbiddenEdges.find(edgeIndex) != forbiddenEdges.end()) continue;
            if (neighbor == end) return true;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return false;
}

bool isConnectedWithout(int a, int b, set<int>& forbiddenEdges) {
    return bfs(a, b, forbiddenEdges);
}

bool checkSubtree(int i) {
    for (int j = 1; j <= 2; ++j) {
        for (int x : subtree[i][j]) {
            for (int y : subtree[i][j]) {
                if (x != y && !isConnectedWithout(x, y, {i})) return false;
            }
        }
    }
    return true;
}

bool checkSubsubtree(int i, int j) {
    int totalSubtrees = 0;
    for (int k = 1; k <= n; ++k) {
        if (subtree[i][j].find(k) != subtree[i][j].end()) {
            totalSubtrees++;
            for (int x : subtree[i][j]) {
                for (int y : subtree[i][j]) {
                    if (x != y && !isConnectedWithout(x, y, {t for t in 1..n-1 if edge[t].u != center[i][j] && edge[t].v != center[i][j]} union {i})) return false;
                }
            }
        }
    }
    return totalSubtrees == count(l for l in 1..n-1 if l != i && (edge[l].u == center[i][j] || edge[l].v == center[i][j]));
}

int main() {
    cin >> n;
    adj.resize(n + 1);
    edges.resize(n - 1);
    subtree.resize(n - 1, vector<set<int>>(2));
    center.resize(n - 1, vector<int>(2));

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 1; j <= 2; ++j) {
            subtree[i][j].insert(edges[i].u);
            subtree[i][j].insert(edges[i].v);
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 1; j <= 2; ++j) {
            center[i][j] = *subtree[i][j].begin();
        }
    }

    bool valid = true;
    for (int i = 0; i < n - 1; ++i) {
        if (!checkSubtree(i)) {
            valid = false;
            break;
        }
    }

    if (valid) {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 1; j <= 2; ++j) {
                if (!checkSubsubtree(i, j)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
    }

    if (valid) {
        for (int i = 0; i < n - 1; ++i) {
            cout << center[i][1] << " " << center[i][2] << endl;
        }
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}
