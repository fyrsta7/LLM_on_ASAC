#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Edge {
    int u, v;
};

vector<vector<int>> adj;
vector<Edge> edges;
vector<vector<set<int>>> subtree;
vector<vector<int>> center;
int n;

bool bfs(int start, int end, set<int> forbiddenEdges) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            int edgeIndex = -1;
            for (int i = 0; i < edges.size(); ++i) {
                if ((edges[i].u == u && edges[i].v == v) || (edges[i].u == v && edges[i].v == u)) {
                    edgeIndex = i;
                    break;
                }
            }
            if (forbiddenEdges.count(edgeIndex)) continue;
            if (v == end) return true;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

bool isValidSubtree(int i, int j) {
    for (int x : subtree[i][j]) {
        for (int y : subtree[i][j]) {
            if (x != y && !bfs(x, y, {i})) return false;
        }
    }
    return true;
}

bool isValidSubsubtree(int i, int j, int k) {
    int centerNode = center[i][j];
    set<int> forbiddenEdges;
    for (int t = 0; t < edges.size(); ++t) {
        if (edges[t].u != centerNode && edges[t].v != centerNode) {
            forbiddenEdges.insert(t);
        }
    }
    forbiddenEdges.insert(i);

    for (int x : subtree[i][j]) {
        for (int y : subtree[i][j]) {
            if (x != y && !bfs(x, y, forbiddenEdges)) return false;
        }
    }
    return true;
}

bool solve() {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!isValidSubtree(i, j)) return false;
            for (int k = 0; k < n; ++k) {
                if (!isValidSubsubtree(i, j, k)) return false;
            }
        }
    }
    return true;
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
        for (int j = 0; j < 2; ++j) {
            int size;
            cin >> size;
            for (int k = 0; k < size; ++k) {
                int node;
                cin >> node;
                subtree[i][j].insert(node);
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> center[i][j];
        }
    }

    if (solve()) {
        for (int i = 0; i < n - 1; ++i) {
            cout << center[i][0] << " " << center[i][1] << endl;
        }
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}
