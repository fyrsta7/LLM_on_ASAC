#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 300 + 5;
const int INF = 1e9;

struct Edge {
    int to, weight;
};

vector<Edge> adj[MAXN];
int dist[MAXN];
int parent[MAXN];
bool visited[MAXN];

void bfs(int start) {
    queue<int> q;
    q.push(start);
    fill(dist, dist + MAXN, INF);
    fill(visited, visited + MAXN, false);
    dist[start] = 0;
    parent[start] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited[u] = true;

        for (const Edge &e : adj[u]) {
            if (!visited[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                parent[e.to] = u;
                q.push(e.to);
            }
        }
    }
}

int findFarthestNode(int start) {
    bfs(start);
    int farthestNode = start;
    for (int i = 1; i < MAXN; ++i) {
        if (dist[i] != INF && dist[i] > dist[farthestNode]) {
            farthestNode = i;
        }
    }
    return farthestNode;
}

int main() {
    int n, s;
    cin >> n >> s;

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int u = findFarthestNode(1);
    int v = findFarthestNode(u);

    vector<int> path;
    for (int x = v; x != -1; x = parent[x]) {
        path.push_back(x);
    }

    int diameter = dist[v];
    int minEccentricity = INF;

    for (int i = 0; i < path.size(); ++i) {
        for (int j = i; j < path.size(); ++j) {
            int pathLength = dist[path[i]] + dist[path[j]] - 2 * dist[path[i]];
            if (pathLength <= s) {
                int eccentricity = 0;
                bfs(path[i]);
                for (int k = 1; k <= n; ++k) {
                    eccentricity = max(eccentricity, dist[k]);
                }
                minEccentricity = min(minEccentricity, eccentricity);
            }
        }
    }

    cout << minEccentricity << endl;
    return 0;
}
