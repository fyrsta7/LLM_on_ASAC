#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Edge {
    int x, y, z;
};

struct UnionFind {
    vector<int> parent;
    vector<int> rank_;
    UnionFind(int n){
        parent.resize(n+1);
        rank_.resize(n+1, 0);
        for(int i=0;i<=n;i++) parent[i]=i;
    }
    int find_set(int x){
        if(parent[x]!=x) parent[x]=find_set(parent[x]);
        return parent[x];
    }
    void union_set(int x, int y){
        int fx = find_set(x);
        int fy = find_set(y);
        if(fx == fy) return;
        if(rank_[fx] < rank_[fy]){
            parent[fx] = fy;
        }
        else{
            parent[fy] = fx;
            if(rank_[fx] == rank_[fy]) rank_[fx]++;
        }
    }
};

const int MAXN = 10001;
const int LOG = 14;
int depth_[MAXN];
int parent_[LOG][MAXN];
int max_edge_[LOG][MAXN];
vector<pair<int, int>> adj_list[MAXN];
int n, m;

void dfs(int u, int p, int w){
    parent_[0][u] = p;
    max_edge_[0][u] = w;
    for(auto &edge : adj_list[u]){
        int v = edge.first;
        int z = edge.second;
        if(v != p){
            depth_[v] = depth_[u] + 1;
            dfs(v, u, z);
        }
    }
}

int get_bottleneck(int u, int v){
    if(u == v) return 0;
    int res = 100000;
    if(depth_[u] < depth_[v]) swap(u, v);
    for(int k=LOG-1; k>=0; k--){
        if(depth_[u] - (1<<k) >= depth_[v]){
            res = min(res, max_edge_[k][u]);
            u = parent_[k][u];
        }
    }
    if(u == v) return res;
    for(int k=LOG-1; k>=0; k--){
        if(parent_[k][u] != -1 && parent_[k][u] != parent_[k][v]){
            res = min(res, max_edge_[k][u]);
            res = min(res, max_edge_[k][v]);
            u = parent_[k][u];
            v = parent_[k][v];
        }
    }
    res = min(res, max_edge_[0][u]);
    res = min(res, max_edge_[0][v]);
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    vector<Edge> edges(m);
    for(int i=0;i<m;i++) cin >> edges[i].x >> edges[i].y >> edges[i].z;
    sort(edges.begin(), edges.end(), [&](const Edge &a, const Edge &b) -> bool{
        return a.z > b.z;
    });
    UnionFind uf(n);
    for(int i=0;i<m;i++){
        int x = edges[i].x;
        int y = edges[i].y;
        int z = edges[i].z;
        if(uf.find_set(x) != uf.find_set(y)){
            uf.union_set(x, y);
            adj_list[x].emplace_back(y, z);
            adj_list[y].emplace_back(x, z);
        }
    }
    memset(parent_, -1, sizeof(parent_));
    for(int i=1;i<=n;i++) {
        if(parent_[0][i]==-1){
            depth_[i] = 0;
            dfs(i, -1, 0);
        }
    }
    for(int k=1; k<LOG; k++){
        for(int v=1; v<=n; v++){
            if(parent_[k-1][v] != -1){
                parent_[k][v] = parent_[k-1][parent_[k-1][v]];
                max_edge_[k][v] = min(max_edge_[k-1][v], max_edge_[k-1][parent_[k-1][v]]);
            }
            else{
                parent_[k][v] = -1;
                max_edge_[k][v] = 100000;
            }
        }
    }
    int q;
    cin >> q;
    while(q--){
        int x, y;
        cin >> x >> y;
        if(uf.find_set(x) != uf.find_set(y)){
            cout << "-1\n";
        }
        else{
            int bottleneck = get_bottleneck(x, y);
            cout << bottleneck << "\n";
        }
    }
}