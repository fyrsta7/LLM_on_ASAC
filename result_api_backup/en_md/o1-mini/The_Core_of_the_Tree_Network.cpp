#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;
const int MAXN = 305;
const ll INF = 1e18;

struct Edge {
    int to;
    int weight;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    ll s;
    cin >> n >> s;
    vector<vector<Edge>> adj(n, vector<Edge>());
    for(int i=0;i<n-1;i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(Edge{v, w});
        adj[v].push_back(Edge{u, w});
    }
    // BFS to find farthest node from node 0
    auto bfs = [&](int start) -> pair<int, vector<ll>>{
        vector<ll> dist(n, INF);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &e: adj[u]){
                int v = e.to;
                if(dist[v] == INF){
                    dist[v] = dist[u] + e.weight;
                    q.push(v);
                }
            }
        }
        int far = start;
        ll max_dist = -1;
        for(int i=0;i<n;i++) if(dist[i] > max_dist){ max_dist = dist[i]; far = i;}
        return {far, dist};
    };
    pair<int, vector<ll>> first_bfs = bfs(0);
    pair<int, vector<ll>> second_bfs = bfs(first_bfs.first);
    int u = first_bfs.first;
    int v = second_bfs.first;
    // To recover the path from u to v
    // BFS from u with parent tracking
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(u);
    parent[u] = -2;
    while(!q.empty()){
        int current = q.front(); q.pop();
        for(auto &e: adj[current]){
            int nei = e.to;
            if(parent[nei]==-1){
                parent[nei] = current;
                q.push(nei);
                if(nei == v) break;
            }
        }
    }
    // Reconstruct path
    vector<int> path;
    int current = v;
    while(current != -2){
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    int m = path.size();
    // Collect edge lengths along the path
    vector<ll> edge_length(m-1, 0);
    for(int i=0;i<m-1;i++){
        int a = path[i];
        int b = path[i+1];
        for(auto &e: adj[a]){
            if(e.to == b){
                edge_length[i] = e.weight;
                break;
            }
        }
    }
    // Precompute distances from each node to each node on the diameter path
    // dist[v][x]: distance from v to path[x]
    vector<vector<ll>> dist_to_path(n, vector<ll>(m, INF));
    for(int x=0; x<m; x++){
        // BFS from path[x]
        vector<ll> dist(n, INF);
        queue<int> qq;
        int start = path[x];
        dist[start] = 0;
        qq.push(start);
        while(!qq.empty()){
            int u_bfs = qq.front(); qq.pop();
            for(auto &e: adj[u_bfs]){
                int v_bfs = e.to;
                if(dist[v_bfs] == INF){
                    dist[v_bfs] = dist[u_bfs] + e.weight;
                    qq.push(v_bfs);
                }
            }
        }
        for(int v_bfs=0; v_bfs<n; v_bfs++) dist_to_path[v_bfs][x] = dist[v_bfs];
    }
    // Enumerate all possible F [i,j] on the path with length <=s
    ll min_ecc = INF;
    // Precompute prefix sums of edge lengths
    vector<ll> prefix(m, 0);
    for(int i=1;i<m;i++) prefix[i] = prefix[i-1] + edge_length[i-1];
    // Initialize min_dist for each F
    // For each start i
    for(int i=0;i<m;i++){
        // Initialize min_dist
        vector<ll> min_dist(n, INF);
        for(int v=0; v<n; v++) min_dist[v] = dist_to_path[v][i];
        // Compute current_max
        ll current_max = 0;
        for(int v=0; v<n; v++) if(min_dist[v] > current_max) current_max = min_dist[v];
        // Check if length 0 (single node) is acceptable
        if(0 <= s && current_max < min_ecc){
            min_ecc = current_max;
        }
        // Extend the path
        for(int j=i+1; j<m; j++){
            ll length = prefix[j] - prefix[i];
            if(length > s) break;
            for(int v=0; v<n; v++) {
                if(dist_to_path[v][j] < min_dist[v]) min_dist[v] = dist_to_path[v][j];
            }
            // Find the max of min_dist
            ll temp_max = 0;
            for(int v=0; v<n; v++) if(min_dist[v] > temp_max) temp_max = min_dist[v];
            if(temp_max < min_ecc){
                min_ecc = temp_max;
            }
        }
    }
    cout << min_ecc;
}