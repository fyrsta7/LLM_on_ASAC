#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, m;
    cin >> N >> m;
    struct Item{
        int weight;
        int value;
        int dep;
    };
    vector<Item> items(m+1);
    for(int i=1;i<=m;i++) cin >> items[i].weight >> items[i].value >> items[i].dep;
    // Build tree
    vector<vector<int>> tree(m+1, vector<int>());
    vector<int> roots;
    for(int i=1;i<=m;i++) {
        if(items[i].dep ==0) roots.push_back(i);
        else tree[items[i].dep].push_back(i);
    }
    // Initialize DP
    vector<long long> dp(N+1, -1e18);
    dp[0]=0;
    // DFS to process each subtree
    function<void(int, vector<long long>&)> dfs = [&](int u, vector<long long> &curr_dp)-> void{
        // Initialize this node's possible options
        vector<pair<int, long long>> opt;
        // Option: take this node
        opt.emplace_back(items[u].weight, (long long)items[u].weight * items[u].value);
        // Process children
        for(auto &v: tree[u]){
            vector<long long> child_dp(N+1, -1e18);
            dfs(v, child_dp);
            // Merge child_dp into opt
            vector<pair<int, long long>> new_opt;
            for(auto &[cw, cv]: opt){
                for(int w=0; w<=N - cw; w++) {
                    if(child_dp[w] != -1e18){
                        new_opt.emplace_back(cw + w, cv + child_dp[w]);
                    }
                }
            }
            opt = move(new_opt);
        }
        // Update current dp with opt
        vector<long long> tmp_dp = curr_dp;
        for(auto &[cw, cv]: opt){
            for(int w=N; w>=cw; w--){
                if(curr_dp[w - cw] != -1e18){
                    tmp_dp[w] = max(tmp_dp[w], curr_dp[w - cw] + cv);
                }
            }
        }
        curr_dp = move(tmp_dp);
    };
    // Process each root
    for(auto &r: roots){
        vector<long long> subtree_dp(N+1, -1e18);
        dfs(r, subtree_dp);
        // Merge subtree_dp into dp
        vector<long long> tmp_dp = dp;
        for(int w=0; w<=N; w++) {
            if(subtree_dp[w] != -1e18){
                for(int j=N; j>=w; j--){
                    if(dp[j - w] != -1e18){
                        tmp_dp[j] = max(tmp_dp[j], dp[j - w] + subtree_dp[w]);
                    }
                }
            }
        }
        dp = move(tmp_dp);
    }
    long long ans = 0;
    for(int w=0; w<=N; w++) ans = max(ans, dp[w]);
    cout << ans;
}