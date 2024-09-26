#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, s;
    cin >> n >> s;
    // Build adjacency list
    vector<vector<pair<int, ll>>> adj(n+1, vector<pair<int, ll>>());
    for(int i=0;i<n-1;i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    // BFS to find farthest node from 1
    auto bfs = [&](int start) -> pair<int, ll> {
        vector<ll> dist(n+1, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &[v, w] : adj[u]){
                if(dist[v]==-1){
                    dist[v] = dist[u] + w;
                    q.push(v);
                }
            }
        }
        int farthest = start;
        ll max_dist = 0;
        for(int i=1;i<=n;i++) if(dist[i] > max_dist){
            max_dist = dist[i];
            farthest = i;
        }
        return {farthest, max_dist};
    };
    pair<int, ll> first = bfs(1);
    pair<int, ll> second = bfs(first.first);
    // Reconstruct path from first.first to second.first
    int u = first.first, v = second.first;
    vector<int> parent(n+1, -1);
    queue<int> q;
    q.push(u);
    parent[u] = 0;
    while(!q.empty()){
        int curr = q.front(); q.pop();
        for(auto &[neighbor, w] : adj[curr]){
            if(parent[neighbor]==-1){
                parent[neighbor] = curr;
                q.push(neighbor);
                if(neighbor == v) break;
            }
        }
    }
    vector<int> path;
    int node = v;
    while(node != 0){
        path.push_back(node);
        node = parent[node];
    }
    reverse(path.begin(), path.end());
    int L = path.size()-1;
    // Compute cumulative distances
    vector<ll> d(L+1, 0);
    for(int i=1;i<=L;i++) {
        // Find the edge weight between path[i-1] and path[i]
        ll w = 0;
        for(auto &[neighbor, weight] : adj[path[i-1]]){
            if(neighbor == path[i]){
                w = weight;
                break;
            }
        }
        d[i] = d[i-1] + w;
    }
    // Multi-source BFS to compute D[j]
    // Initialize
    vector<ll> D(L+1, 0);
    vector<ll> distance_to_path(L+1, 0);
    vector<int> closest(L+1, -1);
    // Initialize queue with path nodes
    struct QNode{
        int node;
        int j;
        ll dist;
    };
    queue<QNode> qq;
    vector<bool> on_path(n+1, false);
    for(int i=0;i<=L;i++) on_path[path[i]] = true;
    for(int i=0;i<=L;i++){
        qq.push(QNode{path[i], i, 0});
        closest[i] = i;
    }
    // BFS
    while(!qq.empty()){
        QNode current = qq.front(); qq.pop();
        for(auto &[neighbor, w] : adj[current.node]){
            if(!on_path[neighbor] && closest[current.j] == -1){
                closest[current.j] = current.j;
                ll ndist = current.dist + w;
                if(D[current.j] < ndist){
                    D[current.j] = ndist;
                }
                qq.push(QNode{neighbor, current.j, ndist});
            }
        }
    }
    // Now, D[j] contains the maximum distance from j to its subtree
    // Binary search on T
    ll left = 0;
    ll right = d[L] + *max_element(D.begin(), D.end());
    while(left < right){
        ll mid = left + (right - left)/2;
        // Compute a_lower and a_upper
        ll a_lower = LLONG_MIN;
        ll a_upper = LLONG_MAX;
        bool feasible = true;
        for(int j=0;j<=L;j++){
            if(mid < D[j]){
                feasible = false;
                break;
            }
            ll temp = mid - D[j];
            ll aj_lower = d[j] - temp;
            ll aj_upper = d[j] + temp;
            a_lower = max(a_lower, aj_lower);
            a_upper = min(a_upper, aj_upper);
            if(a_lower > a_upper){
                feasible = false;
                break;
            }
        }
        if(!feasible || (a_upper - a_lower) > s){
            left = mid +1;
        }
        else{
            right = mid;
        }
    }
    cout << left;
}