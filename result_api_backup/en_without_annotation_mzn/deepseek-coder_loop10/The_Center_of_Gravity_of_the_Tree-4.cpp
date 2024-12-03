#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct Edge {
    int u, v;
};

vector<vector<int>> adj;
vector<Edge> edges;
vector<vector<unordered_set<int>>> subtree;
vector<vector<int>> center;
int n;

bool bfs(int start, int end, unordered_set<int>& avoidEdges) {
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
            if (avoidEdges.find(edgeIndex) != avoidEdges.end()) continue;
            if (neighbor == end) return true;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return false;
}

bool isValidSubtree(int edgeIndex, int side) {
    int u = edges[edgeIndex].u;
    int v = edges[edgeIndex].v;
    int centerNode = center[edgeIndex][side];
    if (centerNode != u && centerNode != v) return false;

    unordered_set<int> avoidEdges = {edgeIndex};
    for (int node : subtree[edgeIndex][side]) {
        for (int otherNode : subtree[edgeIndex][side]) {
            if (node != otherNode && !bfs(node, otherNode, avoidEdges)) {
                return false;
            }
        }
    }
    return true;
}

bool solve() {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!isValidSubtree(i, j)) return false;
        }
    }
    return true;
}

int main() {
    cin >> n;
    adj.resize(n + 1);
    edges.resize(n - 1);
    subtree.resize(n - 1, vector<unordered_set<int>>(2));
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
