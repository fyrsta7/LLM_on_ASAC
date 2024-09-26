#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1, vector<int>());
    vector<vector<int>> reverse_graph(n+1, vector<int>());
    for(int i=0;i<m;i++){
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        reverse_graph[y].push_back(x);
    }
    int s, t;
    cin >> s >> t;
    vector<bool> reachable(n+1, false);
    queue<int> q;
    q.push(t);
    reachable[t] = true;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto &v: reverse_graph[u]){
            if(!reachable[v]){
                reachable[v] = true;
                q.push(v);
            }
        }
    }
    vector<bool> isV(n+1, false);
    for(int u=1; u<=n; u++){
        if(reachable[u]){
            bool ok = true;
            for(auto &v: graph[u]){
                if(!reachable[v]){
                    ok = false;
                    break;
                }
            }
            if(ok){
                isV[u] = true;
            }
        }
    }
    if(!isV[s] || !isV[t]){
        cout << "-1";
        return 0;
    }
    vector<vector<int>> new_graph(n+1, vector<int>());
    for(int u=1; u<=n; u++){
        if(isV[u]){
            for(auto &v: graph[u]){
                if(isV[v]){
                    new_graph[u].push_back(v);
                }
            }
        }
    }
    vector<int> distance(n+1, -1);
    queue<int> q2;
    q2.push(s);
    distance[s] = 0;
    while(!q2.empty()){
        int u = q2.front(); q2.pop();
        for(auto &v: new_graph[u]){
            if(distance[v] == -1){
                distance[v] = distance[u] + 1;
                q2.push(v);
                if(v == t){
                    break;
                }
            }
        }
    }
    cout << distance[t];
}