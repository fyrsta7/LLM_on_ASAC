#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;
struct Edge {
    int to;
    ll w;
};
vector<vector<Edge>> adj;
ll total = 0;

ll road_sum = 0;

ll read_int() {
    ll x;
    cin >> x;
    return x;
}

bool check(ll S, int& cnt) {
    cnt = 0;
    function<ll(int, int)> dfs = [&](int u, int parent) -> ll {
        ll current = 0;
        for(auto &edge: adj[u]){
            int v = edge.to;
            ll w = edge.w;
            if(v == parent) continue;
            ll res = dfs(v, u) + w;
            if(res >= S){
                cnt++;
            }
            else{
                current = max(current, res);
            }
        }
        return current;
    };
    dfs(1, -1);
    return cnt >= m;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    adj.assign(n+1, vector<Edge>());
    for(int i=0;i<n-1;i++){
        int a, b;
        ll c;
        cin >> a >> b >> c;
        adj[a].push_back(Edge{b, c});
        adj[b].push_back(Edge{a, c});
        total += c;
    }
    ll l=0, r=total, ans=0;
    while(l <= r){
        ll mid = l + (r - l)/2;
        int cnt = 0;
        if(check(mid, cnt)){
            ans = mid;
            l = mid +1;
        }
        else{
            r = mid -1;
        }
    }
    cout << ans;
}