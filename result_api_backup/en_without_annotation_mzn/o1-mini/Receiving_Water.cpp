#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, m;
    cin>>n>>m;
    vector<ll> w(n);
    for(auto &x:w) cin>>x;
    if(m >=n){
        ll res = 0;
        for(auto x:w) res = max(res, x);
        cout<<res;
        return 0;
    }
    priority_queue<ll, vector<ll>, std::greater<ll>> pq;
    for(int i=0;i<m;i++) pq.push(0);
    ll makespan=0;
    for(int i=0;i<n;i++){
        ll earliest = pq.top(); pq.pop();
        ll finish = earliest + w[i];
        pq.push(finish);
        makespan = max(makespan, finish);
    }
    cout<<makespan;
}