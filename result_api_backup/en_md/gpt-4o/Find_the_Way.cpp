#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

void bfsReverse(int t, const vector<vector<int>>& graph, vector<bool>& reachable) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(t);
    visited[t] = true;
    reachable[t] = true;

    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                reachable[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int shortestPathBFS(int s, int t, const vector<vector<int>>& graph, const vector<bool>& reachable) {
    int n = graph.size();
    queue<int> q;
    vector<int> distance(n, INF);
    
    q.push(s);
    distance[s] = 0;

    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int neighbor : graph[node]) {
            if (reachable[neighbor] && distance[node] + 1 < distance[neighbor]) {
                distance[neighbor] = distance[node] + 1;
                q.push(neighbor);
            }
        }
    }
    return (distance[t] == INF) ? -1 : distance[t];
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1), reverseGraph(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        reverseGraph[y].push_back(x);
    }

    int s, t;
    cin >> s >> t;

    if (s == t) {
        cout << 0 << endl;
        return 0;
    }

    vector<bool> reachable(n + 1, false);
    bfsReverse(t, reverseGraph, reachable);

    if (!reachable[s]) {
        cout << -1 << endl;
    } else {
        int result = shortestPathBFS(s, t, graph, reachable);
        cout << result << endl;
    }

    return 0;
}