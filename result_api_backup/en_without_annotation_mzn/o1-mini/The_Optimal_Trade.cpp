#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> price(n+1);
    for(int i=1;i<=n;i++) cin>>price[i];
    // Build adjacency list
    vector<vector<int>> adj(n+1, vector<int>());
    for(int i=0;i<m;i++){
        int u, v, t;
        cin>>u>>v>>t;
        adj[u].push_back(v);
        if(t==2){
            adj[v].push_back(u);
        }
    }
    // Initialize
    vector<int> min_price(n+1, INT32_MAX);
    queue<pair<int, int>> q; // pair of node and steps
    min_price[1] = price[1];
    q.push({1, 1});
    // Initialize max_income
    long long max_income = 0;
    // BFS
    while(!q.empty()){
        pair<int, int> current = q.front(); q.pop();
        int u = current.first;
        int steps = current.second;
        if(steps > 2*n) continue;
        for(auto &v: adj[u]){
            // Update min_price for v
            int new_min_price = min(min_price[u], price[v]);
            if(new_min_price < min_price[v]){
                min_price[v] = new_min_price;
                q.push({v, steps+1});
            }
            // Update max_income
            max_income = max(max_income, (long long)price[v] - (long long)min_price[u]);
        }
    }
    if(max_income <0) cout<<0;
    else cout<<max_income;
}