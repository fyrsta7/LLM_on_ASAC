#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<vector<int>> adj(n+1, vector<int>());
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> W(n+1);
    for(int i=1;i<=n;i++) cin>>W[i];
    long long sum_weight=0;
    int max_weight=0;
    for(int c=1;c<=n;c++){
        int deg=adj[c].size();
        if(deg>=2){
            // Find top two W
            int first = 0, second = 0;
            for(auto &u: adj[c]){
                if(W[u] > first){
                    second = first;
                    first = W[u];
                }
                else if(W[u] > second){
                    second = W[u];
                }
            }
            max_weight = max(max_weight, first * second);
        }
        // Compute sum_weight for this node
        if(adj[c].empty()) continue;
        long long sum=0, sum_sq=0;
        for(auto &u: adj[c]){
            sum += W[u];
            sum_sq += (long long)W[u] * W[u];
        }
        sum_weight += (sum * sum - sum_sq);
        sum_weight %= 10007;
    }
    cout<<max_weight<<" "<<sum_weight;
}