#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1, vector<int>());
    for(int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++) {
        sort(adj[i].begin(), adj[i].end());
    }
    vector<int> sequence;
    if(m == n-1){
        // Perform DFS
        vector<bool> visited(n+1, false);
        // Iterative DFS
        stack<int> s;
        s.push(1);
        while(!s.empty()){
            int u = s.top();
            s.pop();
            if(!visited[u]){
                visited[u] = true;
                sequence.push_back(u);
                // Push neighbors in reverse order to visit smallest first
                for(auto it = adj[u].rbegin(); it != adj[u].rend(); ++it){
                    if(!visited[*it]){
                        s.push(*it);
                    }
                }
            }
        }
    }
    else{
        // Perform BFS
        vector<bool> visited(n+1, false);
        priority_queue<int, vector<int>, std::greater<int>> pq;
        pq.push(1);
        visited[1] = true;
        while(!pq.empty()){
            int u = pq.top();
            pq.pop();
            sequence.push_back(u);
            for(auto v: adj[u]){
                if(!visited[v]){
                    pq.push(v);
                    visited[v] = true;
                }
            }
        }
    }
    for(int i=0;i<sequence.size();i++){
        if(i>0) cout << ' ';
        cout << sequence[i];
    }
    return 0;
}