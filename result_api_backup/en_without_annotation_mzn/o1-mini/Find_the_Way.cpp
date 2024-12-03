#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> roads(m);
    vector<vector<int>> adj(n+1, vector<int>());
    vector<vector<int>> radj(n+1, vector<int>());
    for(int i=0;i<m;i++){
        cin >> roads[i].first >> roads[i].second;
        adj[roads[i].first].push_back(i);
        radj[roads[i].second].push_back(i);
    }
    int s, t;
    cin >> s >> t;
    // BFS from t in original graph
    vector<bool> from_t(n+1, false);
    queue<int> q;
    q.push(t);
    from_t[t] = true;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto &road_idx : adj[u]){
            int v = roads[road_idx].first;
            if(!from_t[v]){
                from_t[v] = true;
                q.push(v);
            }
        }
    }
    // BFS from t in reversed graph
    vector<bool> to_t(n+1, false);
    q.push(t);
    to_t[t] = true;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto &road_idx : radj[u]){
            int v = roads[road_idx].second;
            if(!to_t[v]){
                to_t[v] = true;
                q.push(v);
            }
        }
    }
    // BFS from s to find shortest path to t
    vector<int> parent(m, -1);
    vector<int> road_to(n+1, -1);
    queue<int> qs;
    qs.push(s);
    vector<bool> visited(n+1, false);
    visited[s] = true;
    while(!qs.empty()){
        int u = qs.front(); qs.pop();
        for(auto &road_idx : adj[u]){
            int v = roads[road_idx].second;
            if(!visited[v]){
                visited[v] = true;
                road_to[v] = road_idx;
                qs.push(v);
                if(v == t) break;
            }
        }
    }
    if(!visited[t]){
        cout << "-1";
        return 0;
    }
    // Reconstruct path
    vector<int> path_roads;
    int current = t;
    while(current != s){
        int road_idx = road_to[current];
        path_roads.push_back(road_idx);
        current = roads[road_idx].first;
    }
    reverse(path_roads.begin(), path_roads.end());
    // Collect nodes on path
    vector<int> path_nodes;
    path_nodes.push_back(s);
    for(auto &road_idx : path_roads){
        path_nodes.push_back(roads[road_idx].second);
    }
    // Set of nodes on the path
    vector<bool> on_path(n+1, false);
    for(auto &u : path_nodes){
        on_path[u] = true;
    }
    // Check cond2
    bool cond2 = true;
    for(auto &u : path_nodes){
        for(auto &road_idx : adj[u]){
            int v = roads[road_idx].second;
            if(!(from_t[v] || to_t[v])){
                cond2 = false;
                break;
            }
        }
        if(!cond2) break;
    }
    if(cond2){
        cout << (int)(path_roads.size());
    }
    else{
        cout << "-1";
    }
}