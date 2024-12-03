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

struct Graph {
    int n, m;
    vector<Road> roads;
    vector<vector<int>> adj;

    Graph(int n, int m, const vector<Road>& roads) : n(n), m(m), roads(roads) {
        adj.resize(n + 1);
        for (const auto& road : roads) {
            adj[road.u].push_back(road.v);
            adj[road.v].push_back(road.u);
        }
    }

    vector<int> findHamiltonianCycle() {
        vector<int> cycle;
        vector<bool> visited(n + 1, false);
        vector<int> path;
        path.push_back(1);
        visited[1] = true;

        if (dfs(1, visited, path)) {
            cycle = path;
        }

        return cycle;
    }

    bool dfs(int v, vector<bool>& visited, vector<int>& path) {
        if (path.size() == n) {
            if (find(adj[v].begin(), adj[v].end(), 1) != adj[v].end()) {
                path.push_back(1);
                return true;
            }
            return false;
        }

        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                path.push_back(u);
                if (dfs(u, visited, path)) {
                    return true;
                }
                path.pop_back();
                visited[u] = false;
            }
        }

        return false;
    }

    vector<int> computeFirst(const vector<int>& cycle) {
        vector<int> first(n + 1);
        unordered_map<int, int> pos;
        for (int i = 0; i < cycle.size(); ++i) {
            pos[cycle[i]] = i;
        }
        for (int i = 1; i <= n; ++i) {
            first[i] = i;
        }
        sort(first.begin() + 1, first.end(), [&](int a, int b) {
            return pos[a] < pos[b];
        });
        return first;
    }

    int computeScore(const vector<int>& first) {
        int score = 0;
        for (int i = 1; i <= n; ++i) {
            score += pow(n, n - i) * first[i];
        }
        return score;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Road> roads(m);
    for (int i = 0; i < m; ++i) {
        cin >> roads[i].u >> roads[i].v;
    }

    Graph graph(n, m, roads);
    vector<int> cycle = graph.findHamiltonianCycle();
    vector<int> first = graph.computeFirst(cycle);
    int score = graph.computeScore(first);

    for (int i = 1; i <= n; ++i) {
        cout << first[i] << " ";
    }
    cout << endl;

    return 0;
}
