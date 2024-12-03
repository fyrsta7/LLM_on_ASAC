#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1, vector<int>());
    vector<int> in_degree(n+1, 0);
    for(int i=0;i<m;i++){
        int si;
        cin >> si;
        vector<int> S(si);
        for(int j=0;j<si;j++) cin >> S[j];
        int a = S[0];
        int b = S[si-1];
        vector<bool> isStop(n+1, false);
        for(auto x:S) isStop[x] = true;
        for(int z=a; z<=b; z++) {
            if(!isStop[z]){
                for(auto x:S){
                    adj[z].push_back(x);
                    in_degree[x]++;
                }
            }
        }
    }
    // Kahn's algorithm for longest path in DAG
    queue<int> q;
    vector<int> dp(n+1, 1);
    for(int u=1; u<=n; u++) if(in_degree[u]==0) q.push(u);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto v: adj[u]){
            if(dp[v] < dp[u]+1){
                dp[v] = dp[u]+1;
            }
            in_degree[v]--;
            if(in_degree[v]==0){
                q.push(v);
            }
        }
    }
    int res = 0;
    for(int u=1; u<=n; u++) res = max(res, dp[u]);
    cout << res;
}