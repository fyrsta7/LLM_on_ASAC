#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,q;
    cin >> n >> m >> q;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // BFS to find distances from node1
    vector<int> dist(n+1, -1);
    queue<int> qBFS;
    dist[1] = 0;
    qBFS.push(1);
    while(!qBFS.empty()){
        int u = qBFS.front(); qBFS.pop();
        for(auto &v: adj[u]){
            if(dist[v]==-1){
                dist[v]=dist[u]+1;
                qBFS.push(v);
            }
        }
    }
    // Check if the component containing node1 has a cycle
    // A tree has m = n-1 edges
    // Count edges in the component
    // Use DFS
    vector<bool> visited(n+1, false);
    bool hasCycle = false;
    int edgeCount =0;
    function<void(int, int)> dfs = [&](int u, int parent)-> void{
        visited[u]=true;
        for(auto &v: adj[u]){
            edgeCount++;
            if(!visited[v]){
                dfs(v, u);
            }
            else if(v != parent){
                hasCycle = true;
            }
        };
    };
    dfs(1, -1);
    // Each edge is counted twice
    edgeCount /=2;
    if(edgeCount > n-1){
        hasCycle = true;
    }
    // Now process queries
    while(q--){
        int x,t;
        cin >> x >> t;
        if(dist[x]==-1){
            cout << "NO\n";
            continue;
        }
        if(t < dist[x]){
            cout << "NO\n";
            continue;
        }
        if(t == dist[x]){
            cout << "YES\n";
            continue;
        }
        if(hasCycle){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}