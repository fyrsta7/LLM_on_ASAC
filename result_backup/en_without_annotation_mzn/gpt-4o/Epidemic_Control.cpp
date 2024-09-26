#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to, weight;
};

vector<vector<Edge>> adj;
vector<int> army;

int bfs(int start, int end) {
    vector<int> dist(adj.size(), INT_MAX);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (Edge e : adj[curr]) {
            if (dist[e.to] > dist[curr] + e.weight) {
                dist[e.to] = dist[curr] + e.weight;
                q.push(e.to);
            }
        }
    }
    return dist[end];
}

int main() {
    int n, m;
    cin >> n;
    adj.resize(n + 1);
    
    vector<int> u(n - 1), v(n - 1), w(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> u[i] >> v[i] >> w[i];
        adj[u[i]].push_back({v[i], w[i]});
        adj[v[i]].push_back({u[i], w[i]});
    }
    
    cin >> m;
    army.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }
    
    vector<int> camp(m);
    for (int i = 0; i < m; ++i) {
        cin >> camp[i];
    }
    
    int max_time = 0;
    for (int i = 0; i < m; ++i) {
        int time = bfs(army[i], camp[i]);
        max_time = max(max_time, time);
    }
    
    cout << max_time << endl;
    return 0;
}