#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll x1, y1, x2, y2, N;
    cin >> x1 >> y1 >> x2 >> y2 >> N;
    vector<pair<ll, ll>> positions(N);
    for(auto &p: positions) cin >> p.first >> p.second;
    vector<pair<ll, ll>> d(N);
    for(int i=0;i<N;i++) {
        ll dx1 = positions[i].first - x1;
        ll dy1 = positions[i].second - y1;
        ll dx2 = positions[i].first - x2;
        ll dy2 = positions[i].second - y2;
        d[i].first = dx1*dx1 + dy1*dy1;
        d[i].second = dx2*dx2 + dy2*dy2;
    }
    sort(d.begin(), d.end(), [&](const pair<ll,ll> &a, const pair<ll,ll> &b)->bool{
        if(a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });
    vector<ll> suffix_max(N+1, 0);
    suffix_max[N] = 0;
    for(int i=N-1;i>=0;i--){
        suffix_max[i] = max(d[i].second, suffix_max[i+1]);
    }
    ll res = LLONG_MAX;
    for(int k=0;k<=N;k++){
        ll r1 = (k==0) ? 0 : d[k-1].first;
        ll r2 = (k<N) ? suffix_max[k] : 0;
        res = min(res, r1 + r2);
    }
    cout << res;
}