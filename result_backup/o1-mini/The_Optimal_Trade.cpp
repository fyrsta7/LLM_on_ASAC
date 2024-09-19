#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<int> price(n+1);
    for(int i=1;i<=n;i++) cin >> price[i];
    vector<vector<int>> adj(n+1, vector<int>());
    vector<vector<int>> radj(n+1, vector<int>());
    for(int i=0;i<m;i++){
        int x, y, z;
        cin >> x >> y >> z;
        adj[x].push_back(y);
        radj[y].push_back(x);
        if(z == 2){
            adj[y].push_back(x);
            radj[x].push_back(y);
        }
    }
    // First pass DFS
    vector<bool> visited(n+1, false);
    vector<int> order;
    stack<int> s;
    // Iterative DFS
    for(int i=1;i<=n;i++) {
        if(!visited[i]){
            s.push(i);
            while(!s.empty()){
                int u = s.top();
                s.pop();
                if(u < 0){
                    order.push_back(-u);
                    continue;
                }
                if(visited[u]) continue;
                visited[u] = true;
                s.push(-u);
                for(auto &v: adj[u]){
                    if(!visited[v]) s.push(v);
                }
            }
        }
    }
    // Second pass DFS on reversed graph
    int K = 0;
    vector<int> comp(n+1, 0);
    for(int i=order.size()-1;i>=0;i--){
        int u = order[i];
        if(comp[u] == 0){
            K++;
            stack<int> s2;
            s2.push(u);
            while(!s2.empty()){
                int v = s2.top(); s2.pop();
                if(comp[v] != 0) continue;
                comp[v] = K;
                for(auto &w: radj[v]){
                    if(comp[w] == 0) s2.push(w);
                }
            }
        }
    }
    // Build compressed DAG
    vector<vector<int>> cadj(K+1, vector<int>());
    vector<vector<int>> cradj(K+1, vector<int>());
    vector<int> cmin(K+1, INT32_MAX);
    vector<int> cmax(K+1, INT32_MIN);
    for(int u=1; u<=n; u++){
        int cu = comp[u];
        cmin[cu] = min(cmin[cu], price[u]);
        cmax[cu] = max(cmax[cu], price[u]);
        for(auto &v: adj[u]){
            int cv = comp[v];
            if(cu != cv){
                cadj[cu].push_back(cv);
                cradj[cv].push_back(cu);
            }
        }
    }
    // Remove duplicate edges
    for(int i=1;i<=K;i++){
        sort(cadj[i].begin(), cadj[i].end());
        cadj[i].erase(unique(cadj[i].begin(), cadj[i].end()), cadj[i].end());
    }
    // Find components reachable from 1
    int c1 = comp[1];
    vector<bool> reachable(K+1, false);
    stack<int> s_reach;
    s_reach.push(c1);
    reachable[c1] = true;
    while(!s_reach.empty()){
        int u = s_reach.top(); s_reach.pop();
        for(auto &v: cadj[u]){
            if(!reachable[v]){
                reachable[v] = true;
                s_reach.push(v);
            }
        }
    }
    // Find components that can reach n
    int cn = comp[n];
    vector<bool> can_reach_n(K+1, false);
    stack<int> s_reach_n;
    s_reach_n.push(cn);
    can_reach_n[cn] = true;
    while(!s_reach_n.empty()){
        int u = s_reach_n.top(); s_reach_n.pop();
        for(auto &v: cradj[u]){
            if(!can_reach_n[v]){
                can_reach_n[v] = true;
                s_reach_n.push(v);
            }
        }
    }
    // Keep only components that are reachable from 1 and can reach n
    vector<bool> valid(K+1, false);
    for(int i=1;i<=K;i++) if(reachable[i] && can_reach_n[i]) valid[i] = true;
    // Rebuild compressed DAG with valid components
    vector<vector<int>> final_cadj(K+1, vector<int>());
    vector<int> indegree(K+1, 0);
    for(int u=1; u<=K; u++) if(valid[u]){
        for(auto &v: cadj[u]){
            if(valid[v]){
                final_cadj[u].push_back(v);
                indegree[v]++;
            }
        }
    }
    // Topological sort using Kahn's algorithm
    queue<int> q;
    for(int i=1;i<=K;i++) if(valid[i] && indegree[i] == 0) q.push(i);
    vector<int> topo;
    while(!q.empty()){
        int u = q.front(); q.pop();
        topo.push_back(u);
        for(auto &v: final_cadj[u]){
            indegree[v]--;
            if(indegree[v] == 0) q.push(v);
        }
    }
    // Process in topological order
    long long global_min = INT32_MAX;
    long long global_max = LLONG_MIN;
    for(auto &u: topo){
        global_min = min((long long)global_min, (long long)cmin[u]);
        long long diff = (long long)cmax[u] - (long long)global_min;
        if(diff > global_max) global_max = diff;
    }
    if(global_max > 0) cout << global_max;
    else cout << 0;
}