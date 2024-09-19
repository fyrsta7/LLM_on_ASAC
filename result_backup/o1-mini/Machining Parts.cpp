#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // BFS to find girth
    int girth = INF;
    vector<int> dist_tmp(n+1, -1);
    for(int u=1; u<=n && girth >3; u++){
        fill(dist_tmp.begin(), dist_tmp.end(), -1);
        queue<int> q_bfs;
        dist_tmp[u] = 0;
        q_bfs.push(u);
        while(!q_bfs.empty()){
            int current = q_bfs.front(); q_bfs.pop();
            for(auto &v: adj[current]){
                if(dist_tmp[v]==-1){
                    dist_tmp[v] = dist_tmp[current]+1;
                    q_bfs.push(v);
                }
                else if(v != (dist_tmp[current]>0 ? -1 : -1)){
                    if(v != current){
                        girth = min(girth, dist_tmp[current] + dist_tmp[v] +1);
                        if(girth ==3) break;
                    }
                }
            }
            if(girth ==3) break;
        }
    }
    // BFS from node 1 to find distances
    vector<int> dist(n+1, -1);
    queue<int> q_dist;
    dist[1] =0;
    q_dist.push(1);
    while(!q_dist.empty()){
        int current = q_dist.front(); q_dist.pop();
        for(auto &v: adj[current]){
            if(dist[v]==-1){
                dist[v] = dist[current]+1;
                q_dist.push(v);
            }
        }
    }
    while(q--){
        int a;
        ll L;
        cin >> a >> L;
        if(a ==1){
            if(L ==0){
                cout << "Yes\n";
            }
            else{
                if(girth <= L || (L %2 ==0)){
                    cout << "Yes\n";
                }
                else{
                    cout << "No\n";
                }
            }
        }
        else{
            if(dist[a]==-1){
                cout << "No\n";
                continue;
            }
            int d = dist[a];
            if(L < d){
                cout << "No\n";
            }
            else{
                ll delta = L - d;
                if(delta ==0){
                    cout << "Yes\n";
                }
                else{
                    if(delta %2 ==0){
                        cout << "Yes\n";
                    }
                    else{
                        if(girth <= L - d){
                            cout << "Yes\n";
                        }
                        else{
                            cout << "No\n";
                        }
                    }
                }
            }
        }
    }
}