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
        vector<int> route;
        vector<bool> visited(n + 1, false);
        vector<int> path;
        path.push_back(1);
        visited[1] = true;

        if (dfs(1, visited, path)) {
            route = path;
        }

        return route;
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

    vector<int> calculateFirst(const vector<int>& route) {
        vector<int> first(n + 1);
        unordered_map<int, int> first_pos;
        for (int i = 0; i < route.size(); ++i) {
            if (first_pos.find(route[i]) == first_pos.end()) {
                first_pos[route[i]] = i + 1;
            }
        }
        for (int i = 1; i <= n; ++i) {
            first[i] = first_pos[i];
        }
        return first;
    }

    int calculateScore(const vector<int>& first) {
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
    vector<int> route = graph.findHamiltonianCycle();
    vector<int> first = graph.calculateFirst(route);
    int score = graph.calculateScore(first);

    for (int i = 1; i <= n; ++i) {
        cout << first[i] << " ";
    }
    cout << endl;

    return 0;
}
