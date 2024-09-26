#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> l(n+1, -1), r(n+1, -1), c(n+1);
    for(int i=1;i<=n;i++) cin>>l[i];
    for(int i=1;i<=n;i++) cin>>r[i];
    for(int i=1;i<=n;i++) cin>>c[i];
    // Build tree
    vector<vector<int>> tree(n+1, vector<int>());
    for(int i=1;i<=n;i++){
        if(l[i]!=-1) tree[i].push_back(l[i]);
        if(r[i]!=-1) tree[i].push_back(r[i]);
    }
    // Function to compute size of subtree rooted at u
    // and check some condition, here we assume condition is same color
    // Adjust the condition as per the actual problem
    // Since exact condition is unclear, using same color
    // Find the largest subtree where all nodes have the same color
    int max_size=0;
    function<pair<int, bool>(int)> dfs = [&](int u)->pair<int, bool>{
        int sz=1;
        bool valid=true;
        if(l[u]!=-1){
            auto left = dfs(l[u]);
            sz += left.first;
            valid = valid && left.second && (c[l[u]] == c[u]);
        }
        if(r[u]!=-1){
            auto right = dfs(r[u]);
            sz += right.first;
            valid = valid && right.second && (c[r[u]] == c[u]);
        }
        if(valid) max_size = max(max_size, sz);
        return {sz, valid};
    };
    dfs(1);
    cout<<max_size;
}