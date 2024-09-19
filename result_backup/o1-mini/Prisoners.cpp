#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

bool is_bipartite(int N, const vector<pair<int, int>> &edges) {
    vector<int> color(N + 1, -1);
    vector<vector<int>> adj(N + 1);
    for(auto &p : edges){
        adj[p.first].push_back(p.second);
        adj[p.second].push_back(p.first);
    }
    for(int i=1;i<=N;i++){
        if(color[i]==-1){
            queue<int> q;
            q.push(i);
            color[i]=0;
            while(!q.empty()){
                int u = q.front(); q.pop();
                for(auto &v : adj[u]){
                    if(color[v]==-1){
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if(color[v] == color[u]){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N,M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for(int i=0;i<M;i++) cin >> edges[i].a >> edges[i].b >> edges[i].c;
    sort(edges.begin(), edges.end(), [&](const Edge &x, const Edge &y) -> bool{
        return x.c < y.c;
    });
    int left = 0, right = 1000000000;
    int ans = 0;
    while(left <= right){
        int mid = left + (right - left)/2;
        // Find first edge with c > mid
        int p = upper_bound(edges.begin(), edges.end(), mid, [&](const int val, const Edge &e) -> bool{
            return val < e.c;
        }) - edges.begin();
        // Collect edges > mid
        vector<pair<int, int>> current_edges;
        for(int i=p;i<M;i++) current_edges.emplace_back(make_pair(edges[i].a, edges[i].b));
        if(is_bipartite(N, current_edges)){
            ans = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    // Check if there are no conflicts
    // If all edges can be placed in different prisons, ans=0
    // Otherwise, ans is as computed
    // But according to binary search, ans is correctly computed
    // Now, find if ans is 0 and there are no conflicts
    if(M ==0){
        cout << "0";
    }
    else{
        // Check if ans is such that there are no edges >ans or if bipartite
        // As per binary search, it's correct
        cout << ans;
    }
}