#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1, vector<int>());
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<long long> W(n+1, 0);
    for(int i=1;i<=n;i++) cin >> W[i];
    long long total_sum = 0;
    long long global_max = 0;
    for(int x=1;x<=n;x++){
        int deg = adj[x].size();
        if(deg ==0) continue;
        long long sumW =0;
        long long sumW2=0;
        long long max1 = -1, max2 = -1;
        for(auto &u: adj[x]){
            sumW += W[u];
            sumW2 += W[u] * W[u];
            if(W[u] > max1){
                max2 = max1;
                max1 = W[u];
            }
            else if(W[u] > max2){
                max2 = W[u];
            }
        }
        if(deg >=2){
            long long product = max1 * max2;
            if(product > global_max) global_max = product;
        }
        long long temp = (sumW % 10007) * (sumW % 10007) % 10007;
        temp = (temp - (sumW2 % 10007) + 10007) % 10007;
        total_sum = (total_sum + temp) % 10007;
    }
    cout << global_max << " " << total_sum;
}