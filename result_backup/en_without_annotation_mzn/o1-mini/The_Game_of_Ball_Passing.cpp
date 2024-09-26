#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    int n, m;
    cin >> n >> m;
    if(n ==1){
        cout << "1\n";
        return 0;
    }
    vector<vector<int>> neighbors(n+1, vector<int>());
    for(int a=1; a<=n; a++){
        if(a >1) neighbors[a].push_back(a-1);
        else neighbors[a].push_back(n);
        if(a <n) neighbors[a].push_back(a+1);
        else neighbors[a].push_back(1);
    }
    vector<ll> prev(n+1,0);
    prev[1] =1;
    for(int step=2; step<=m+1; step++){
        vector<ll> curr(n+1,0);
        for(int a=1; a<=n; a++){
            for(auto &b: neighbors[a]){
                curr[a] += prev[b];
            }
        }
        prev = curr;
    }
    ll num = prev[1];
    ll bound = (1LL << m);
    if(num >= bound){
        num = bound -1;
    }
    cout << num << "\n";
}