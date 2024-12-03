#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int cost;
    int id;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    // Initialize adjacency list
    vector<vector<Edge>> adj(n+1, vector<Edge>());
    // Read roads
    for(int i=1; i<=n-1; i++){
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back(Edge{v, c, i});
        adj[v].push_back(Edge{u, c, i});
    }
    // HLD variables
    vector<int> size_vec(n+1, 0);
    vector<int> depth_vec(n+1, 0);
    vector<int> parent_vec(n+1, 0);
    vector<int> heavy(n+1, -1);
    vector<int> head(n+1, 0);
    vector<int> pos(n+1, 0);
    vector<int> edge_at_pos(n+1, 0);
    int current_pos = 1;
    // DFS to compute sizes and heavy child
    // Using iterative DFS to avoid stack overflow
    stack<pair<int, int>> st_dfs;
    st_dfs.emplace(1, -1);
    while(!st_dfs.empty()){
        pair<int, int> p = st_dfs.top(); st_dfs.pop();
        int u = p.first, p_u = p.second;
        if(u < 0){
            u = -u;
            // Post-processing
            for(auto &e: adj[u]){
                int v = e.to;
                if(v != p_u){
                    size_vec[u] += size_vec[v];
                    if(heavy[u]==-1 || size_vec[v] > size_vec[heavy[u]]){
                        heavy[u] = v;
                    }
                }
            }
            continue;
        }
        // Pre-processing
        st_dfs.emplace(-u, p_u);
        for(auto &e: adj[u]){
            int v = e.to;
            if(v != p_u){
                depth_vec[v] = depth_vec[u] +1;
                parent_vec[v] = u;
                st_dfs.emplace(v, u);
            }
        }
    }
    // DFS to assign head and pos
    stack<pair<int, int>> st_hld;
    st_hld.emplace(1, 1);
    while(!st_hld.empty()){
        pair<int, int> p = st_hld.top(); st_hld.pop();
        int u = p.first, h = p.second;
        head[u] = h;
        pos[u] = current_pos;
        if(u != h){
            // Assign edge_at_pos
            for(auto &e: adj[u]){
                if(e.to == parent_vec[u]){
                    edge_at_pos[current_pos] = e.id;
                    break;
                }
            }
        }
        current_pos++;
        if(heavy[u] != -1){
            st_hld.emplace(heavy[u], h);
            for(auto &e: adj[u]){
                int v = e.to;
                if(v != parent_vec[u] && v != heavy[u]){
                    st_hld.emplace(v, v);
                }
            }
        }
    }
    // Initialize BIT
    int size_bit = n+1;
    vector<long long> bit(size_bit, 0LL);
    auto update = [&](auto &update_ref, int idx, long long delta) -> void{
        while(idx < size_bit){
            bit[idx] += delta;
            idx += idx & (-idx);
        }
    };
    auto query = [&](auto &query_ref, int idx) -> long long{
        long long res = 0;
        while(idx >0){
            res += bit[idx];
            idx -= idx & (-idx);
        }
        return res;
    };
    // Assign edge costs to BIT
    for(int u=1; u<=n; u++){
        if(u != 1){
            int e_id = edge_at_pos[pos[u]];
            // Find the edge cost
            for(auto &e: adj[u]){
                if(e.to == parent_vec[u]){
                    update(update, pos[u], (long long)e.cost);
                    break;
                }
            }
        }
    }
    // Read all m plans
    vector<pair<int, int>> plans(m);
    for(int i=0; i<m; i++) cin >> plans[i].first >> plans[i].second;
    // First pass: compute C_i, global_max, second_max, count_paths_max, and e.max_c
    long long global_max = 0, second_max = 0;
    int count_paths_max = 0;
    vector<long long> C_i(m, 0LL);
    // Initialize edge_data
    // max_c[e] = maximum C_i over paths including e
    // paths_with_max_and_include_e[e] = number of max paths including e
    vector<long long> max_c(n, 0LL);
    vector<int> paths_with_max(n, 0);
    // Function to compute path sum and update max_c
    auto traverse_and_update = [&](int u, int v, long long &ci) -> void{
        long long res =0;
        while(head[u] != head[v]){
            if(depth_vec[head[u]] > depth_vec[head[v]]){
                // from head[u] to u
                res += query(query, pos[u]) - query(query, pos[head[u]]-1);
                u = parent_vec[head[u]];
            }
            else{
                res += query(query, pos[v]) - query(query, pos[head[v]]-1);
                v = parent_vec[head[v]];
            }
        }
        if(u == v){
            // Do nothing
        }
        else{
            if(depth_vec[u] > depth_vec[v]){
                res += query(query, pos[u]) - query(query, pos[v]+1);
            }
            else{
                res += query(query, pos[v]) - query(query, pos[u]+1);
            }
        }
        ci = res;
    };
    for(int i=0; i<m; i++){
        int u = plans[i].first, v = plans[i].second;
        traverse_and_update(u, v, C_i[i]);
        if(C_i[i] > global_max){
            second_max = global_max;
            global_max = C_i[i];
            count_paths_max =1;
        }
        else if(C_i[i] == global_max){
            count_paths_max +=1;
        }
        else{
            if(C_i[i] > second_max){
                second_max = C_i[i];
            }
        }
        // Now traverse the path again to update max_c
        u = plans[i].first, v = plans[i].second;
        while(head[u] != head[v]){
            if(depth_vec[head[u]] > depth_vec[head[v]]){
                // from head[u] to u
                for(int i_pos = pos[head[u]]; i_pos <= pos[u]; i_pos++){
                    int e_id = edge_at_pos[i_pos];
                    if(C_i[i] > max_c[e_id]) max_c[e_id] = C_i[i];
                }
                u = parent_vec[head[u]];
            }
            else{
                // from head[v] to v
                for(int i_pos = pos[head[v]]; i_pos <= pos[v]; i_pos++){
                    int e_id = edge_at_pos[i_pos];
                    if(C_i[i] > max_c[e_id]) max_c[e_id] = C_i[i];
                }
                v = parent_vec[head[v]];
            }
        }
        if(u != v){
            if(depth_vec[u] > depth_vec[v]){
                for(int i_pos = pos[v]+1; i_pos <= pos[u]; i_pos++){
                    int e_id = edge_at_pos[i_pos];
                    if(C_i[i] > max_c[e_id]) max_c[e_id] = C_i[i];
                }
            }
            else{
                for(int i_pos = pos[u]+1; i_pos <= pos[v]; i_pos++){
                    int e_id = edge_at_pos[i_pos];
                    if(C_i[i] > max_c[e_id]) max_c[e_id] = C_i[i];
                }
            }
        }
    }
    // Second pass: count paths_with_max_and_include_e
    for(int i=0; i<m; i++) {
        if(C_i[i] == global_max){
            int u = plans[i].first, v = plans[i].second;
            while(head[u] != head[v]){
                if(depth_vec[head[u]] > depth_vec[head[v]]){
                    // from head[u] to u
                    for(int i_pos = pos[head[u]]; i_pos <= pos[u]; i_pos++){
                        int e_id = edge_at_pos[i_pos];
                        paths_with_max[e_id] +=1;
                    }
                    u = parent_vec[head[u]];
                }
                else{
                    // from head[v] to v
                    for(int i_pos = pos[head[v]]; i_pos <= pos[v]; i_pos++){
                        int e_id = edge_at_pos[i_pos];
                        paths_with_max[e_id] +=1;
                    }
                    v = parent_vec[head[v]];
                }
            }
            if(u != v){
                if(depth_vec[u] > depth_vec[v]){
                    for(int i_pos = pos[v]+1; i_pos <= pos[u]; i_pos++){
                        int e_id = edge_at_pos[i_pos];
                        paths_with_max[e_id] +=1;
                    }
                }
                else{
                    for(int i_pos = pos[u]+1; i_pos <= pos[v]; i_pos++){
                        int e_id = edge_at_pos[i_pos];
                        paths_with_max[e_id] +=1;
                    }
                }
            }
        }
    }
    // Now find the minimum new_max
    long long result = LLONG_MAX;
    for(int e=1; e<=n-1; e++){
        long long using_e_max = max_c[e] - 0;
        if(using_e_max < 0) using_e_max =0;
        long long not_using_e_max;
        if(count_paths_max - paths_with_max[e] >0){
            not_using_e_max = global_max;
        }
        else{
            not_using_e_max = second_max;
        }
        // When setting e to zero, the paths that include e will have their C_i reduced by edge cost
        // So using_e_max should be max C_i - edge_cost
        // But already max_c[e] is max C_i over paths including e
        // Thus, using_e_max = max_c[e] - edge_cost[e]
        // Find edge_cost[e]
        // Find edge_cost
        // Iterate roads again
        // To optimize, store edge_costs
    }
    // To store edge_costs
    vector<int> edge_cost(n, 0);
    for(int u=1; u<=n; u++){
        if(u !=1){
            int e_id = edge_at_pos[pos[u]];
            for(auto &e: adj[u]){
                if(e.to == parent_vec[u]){
                    edge_cost[e_id] = e.cost;
                    break;
                }
            }
        }
    }
    for(int e=1; e<=n-1; e++){
        long long using_e_max = (max_c[e] > 0LL) ? (max_c[e] - (long long)edge_cost[e]) : 0LL;
        if(using_e_max <0) using_e_max =0;
        long long not_using_e_max;
        if(count_paths_max - paths_with_max[e] >0){
            not_using_e_max = global_max;
        }
        else{
            not_using_e_max = second_max;
        }
        long long new_max = max(not_using_e_max, using_e_max);
        result = min(result, new_max);
    }
    cout << result;
}