#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1, vector<int>());
    for(int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Sort adjacency lists to ensure lex order
    for(int i=1;i<=n;i++) sort(adj[i].begin(), adj[i].end());
    // Initialize variables to store the best permutation
    vector<int> best;
    // Initialize permutation starting from 1
    vector<int> perm = {1};
    vector<bool> visited(n+1, false);
    visited[1] = true;
    // Backtracking function
    function<bool(vector<int>&, vector<bool>&)> backtrack = [&](vector<int>& path, vector<bool>& vis) -> bool{
        if(path.size() == n){
            // Check if last connects to first
            if(find(adj[path.back()].begin(), adj[path.back()].end(), path[0]) != adj[path.back()].end()){
                best = path;
                return true;
            }
            return false;
        }
        // Get the last node in the path
        int last = path.back();
        for(auto &neighbor: adj[last]){
            if(!vis[neighbor]){
                vis[neighbor] = true;
                path.push_back(neighbor);
                if(backtrack(path, vis)) return true;
                path.pop_back();
                vis[neighbor] = false;
            }
        }
        return false;
    };
    if(backtrack(perm, visited)){
        for(int i=0;i<best.size();i++) cout << best[i] << (i<best.size()-1?" ":"\n");
    }
    else{
        // If no Hamiltonian cycle exists, output nothing or handle accordingly
    }
}