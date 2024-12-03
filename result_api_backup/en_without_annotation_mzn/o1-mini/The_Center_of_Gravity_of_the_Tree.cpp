#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to find the center(s) of a tree
vector<int> find_centers(int n, const vector<vector<int>>& adj, const vector<int>& nodes){
    vector<int> degree(n+1, 0);
    for(auto u : nodes){
        for(auto v : adj[u]){
            if(find(nodes.begin(), nodes.end(), v) != nodes.end()){
                degree[u]++;
            }
        }
    }
    queue<int> q;
    vector<int> temp;
    for(auto u : nodes){
        if(degree[u] <=1){
            q.push(u);
        }
    }
    int cnt = nodes.size();
    while(cnt > 2){
        int size = q.size();
        cnt -= size;
        for(int i=0;i<size;i++){
            int u = q.front(); q.pop();
            for(auto v : adj[u]){
                if(find(nodes.begin(), nodes.end(), v) != nodes.end()){
                    degree[v]--;
                    if(degree[v] ==1){
                        q.push(v);
                    }
                }
            }
        }
    }
    vector<int> centers;
    while(!q.empty()){
        centers.push_back(q.front());
        q.pop();
    }
    return centers;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<pair<int,int>> edges(n-1);
    vector<vector<int>> adj(n+1, vector<int>());
    for(int i=0;i<n-1;i++){
        cin>>edges[i].first>>edges[i].second;
        adj[edges[i].first].push_back(edges[i].second);
        adj[edges[i].second].push_back(edges[i].first);
    }
    // For each edge, find two subtrees
    for(int i=0;i<n-1;i++){
        int u = edges[i].first;
        int v = edges[i].second;
        // Remove edge i
        // Do BFS from u
        vector<int> nodes1;
        vector<bool> visited(n+1, false);
        queue<int> q;
        q.push(u);
        visited[u]=true;
        while(!q.empty()){
            int curr = q.front(); q.pop();
            nodes1.push_back(curr);
            for(auto neighbor : adj[curr]){
                if(!visited[neighbor] && !( (curr ==u && neighbor ==v) || (curr ==v && neighbor ==u))){
                    visited[neighbor]=true;
                    q.push(neighbor);
                }
            }
        }
        // The other subtree
        vector<int> nodes2;
        for(int j=1;j<=n;j++) if(!visited[j]) nodes2.push_back(j);
        // Find centers
        vector<int> centers1 = find_centers(n, adj, nodes1);
        vector<int> centers2 = find_centers(n, adj, nodes2);
        // Output centers
        for(auto c:centers1) cout<<c<<" ";
        for(auto c:centers2) cout<<c<<" ";
    }
    return 0;
}