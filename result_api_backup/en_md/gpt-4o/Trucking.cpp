#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to, weight;
};

const int INF = 1e9 + 5;
const int MAXN = 10005;

vector<Edge> graph[MAXN];
int maxWeight[MAXN];

bool bfs(int s, int t, int limit) {
    queue<int> q;
    vector<bool> visited(MAXN, false);
    q.push(s);
    visited[s] = true;
    
    while (!q.empty()) {
        int node = q.front(); q.pop();
        if (node == t) return true;
        
        for (auto &edge : graph[node]) {
            if (!visited[edge.to] && edge.weight >= limit) {
                visited[edge.to] = true;
                q.push(edge.to);
            }
        }
    }
    return false;
}

int binary_search_max_weight(int s, int t) {
    int left = 0, right = INF;
    while (left < right) {
        int mid = (right + left + 1) / 2;
        if (bfs(s, t, mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return (left == 0) ? -1 : left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }
    
    int q;
    cin >> q;
    
    while (q--) {
        int x, y;
        cin >> x >> y;
        int result = binary_search_max_weight(x, y);
        cout << result << "\n";
    }
    
    return 0;
}