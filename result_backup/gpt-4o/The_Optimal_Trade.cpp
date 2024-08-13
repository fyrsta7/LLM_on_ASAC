#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9 + 5;

struct Edge {
    int to, weight;
};

void dfs(int v, vector<vector<Edge>>& reverse_graph, vector<bool>& visited) {
    visited[v] = true;
    for (auto& edge : reverse_graph[v]) {
        if (!visited[edge.to]) {
            dfs(edge.to, reverse_graph, visited);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> prices(n);
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }
    
    vector<vector<Edge>> graph(n), reverse_graph(n);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--; y--;
        graph[x].push_back({y, 1});
        reverse_graph[y].push_back({x, 1});
        if (z == 2) {
            graph[y].push_back({x, 1});
            reverse_graph[x].push_back({y, 1});
        }
    }
    
    vector<bool> visited_from_start(n, false), visited_from_end(n, false);
    dfs(0, reverse_graph, visited_from_end);
    dfs(n - 1, graph, visited_from_start);
    
    vector<int> max_diff(n, -INF);
    vector<int> min_price(n, INF);
    queue<int> q;
    
    if (visited_from_end[0] && visited_from_start[0]) {
        q.push(0);
        min_price[0] = prices[0];
        max_diff[0] = 0;
    }
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (auto& edge : graph[curr]) {
            int next = edge.to;
            
            if (visited_from_end[next] && visited_from_start[next]) {
                if (max_diff[next] < max(max_diff[curr], prices[next] - min_price[curr])) {
                    max_diff[next] = max(max_diff[curr], prices[next] - min_price[curr]);
                    q.push(next);
                }
                
                if (min_price[next] > min(min_price[curr], prices[next])) {
                    min_price[next] = min(min_price[curr], prices[next]);
                    q.push(next);
                }
            }
        }
    }
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (visited_from_end[i] && visited_from_start[i]) {
            result = max(result, max_diff[i]);
        }
    }
    
    cout << result << endl;
    return 0;
}
