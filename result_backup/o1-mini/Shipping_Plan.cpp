#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long ll;

const int MAX = 100005;
const int LOG = 20;

int n, m;
vector<vector<pair<int, int>>> adj(100005);
int parent_node[100005];
int depth_node[100005];
ll sum_node[100005];
ll t_e[100005];
ll up_table[20][100005];
ll path_values[100005];
int u_list[100005];
int v_list[100005];
ll max_path = 0;
ll second_max_path = 0;
int count_max_path = 0;
ll max_path_passing_e[100005];
int count_max_passing_e[100005];

void dfs(int u, int p){
    parent_node[u] = p;
    up_table[0][u] = p;
    for(auto &edge: adj[u]){
        int v = edge.first;
        ll t = edge.second;
        if(v != p){
            depth_node[v] = depth_node[u] + 1;
            t_e[v] = t;
            sum_node[v] = sum_node[u] + t;
            dfs(v, u);
        }
    }
}

int lca_func(int u, int v){
    if(depth_node[u] < depth_node[v]){
        swap(u, v);
    }
    for(int k = LOG-1; k >=0; k--){
        if(depth_node[u] - (1<<k) >= depth_node[v]){
            u = up_table[k][u];
        }
    }
    if(u == v){
        return u;
    }
    for(int k = LOG-1; k >=0; k--){
        if(up_table[k][u] != up_table[k][v]){
            u = up_table[k][u];
            v = up_table[k][v];
        }
    }
    return parent_node[u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i=0;i<n-1;i++){
        int a, b, t;
        cin >> a >> b >> t;
        adj[a].emplace_back(b, t);
        adj[b].emplace_back(a, t);
    }
    // Initialize
    parent_node[1] = 1;
    depth_node[1] = 0;
    sum_node[1] = 0;
    t_e[1] = 0;
    // DFS to set parent, depth, sum_node
    dfs(1, 1);
    // Build up_table
    for(int k=1;k<LOG;k++){
        for(int v=1; v<=n; v++){
            up_table[k][v] = up_table[k-1][ up_table[k-1][v] ];
        }
    }
    // Read all paths and compute path[j]
    for(int j=0; j<m; j++){
        int u, v;
        cin >> u >> v;
        u_list[j] = u;
        v_list[j] = v;
        int lca_uv = lca_func(u, v);
        ll path_len = sum_node[u] + sum_node[v] - 2 * sum_node[lca_uv];
        path_values[j] = path_len;
        if(path_len > max_path){
            second_max_path = max_path;
            max_path = path_len;
            count_max_path = 1;
        }
        else if(path_len == max_path){
            count_max_path +=1;
        }
        else{
            if(path_len > second_max_path){
                second_max_path = path_len;
            }
        }
    }
    // Initialize max_path_passing_e and count_max_passing_e
    memset(max_path_passing_e, 0, sizeof(max_path_passing_e));
    memset(count_max_passing_e, 0, sizeof(count_max_passing_e));
    // Function to update edges on path
    for(int j=0; j<m; j++){
        int u = u_list[j];
        int v = v_list[j];
        int lca_uv = lca_func(u, v);
        // From u to lca
        int current = u;
        while(current != lca_uv){
            ll current_path = path_values[j];
            if(current_path > max_path_passing_e[current]){
                max_path_passing_e[current] = current_path;
            }
            if(path_values[j] == max_path){
                count_max_passing_e[current] +=1;
            }
            current = parent_node[current];
        }
        // From v to lca
        current = v;
        while(current != lca_uv){
            ll current_path = path_values[j];
            if(current_path > max_path_passing_e[current]){
                max_path_passing_e[current] = current_path;
            }
            if(path_values[j] == max_path){
                count_max_passing_e[current] +=1;
            }
            current = parent_node[current];
        }
    }
    // Now iterate over all edges and compute the answer
    ll answer = 1e18;
    for(int e=2; e<=n; e++){
        ll A;
        if(max_path_passing_e[e] == max_path && count_max_passing_e[e] == count_max_path){
            A = second_max_path;
        }
        else{
            A = max_path;
        }
        ll B = max_path_passing_e[e] - t_e[e];
        if(B < 0){
            B = 0;
        }
        ll completion_time = max(A, B);
        if(completion_time < answer){
            answer = completion_time;
        }
    }
    cout << answer;
}