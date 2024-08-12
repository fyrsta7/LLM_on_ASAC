#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

void bfs(int start, const vector<vector<int>>& adj, unordered_set<int>& reachable) {
    queue<int> q;
    q.push(start);
    reachable.insert(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (reachable.insert(neighbor).second) {
                q.push(neighbor);
            }
        }
    }
}

int bfsShortestPath(int start, int end, const vector<vector<int>>& adj, const unordered_set<int>& validNodes) {
    queue<int> q;
    q.push(start);
    vector<int> distance(adj.size(), -1);
    distance[start] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (validNodes.count(neighbor) && distance[neighbor] == -1) {
                distance[neighbor] = distance[node] + 1;
                q.push(neighbor);
                if (neighbor == end) {
                    return distance[neighbor];
                }
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);
    
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        rev_adj[y].push_back(x);
    }

    int s, t;
    cin >> s >> t;

    unordered_set<int> reachableFromT;
    bfs(t, rev_adj, reachableFromT);

    if (reachableFromT.count(s) == 0) {
        cout << -1 << endl;
        return 0;
    }

    int result = bfsShortestPath(s, t, adj, reachableFromT);
    cout << result << endl;

    return 0;
}