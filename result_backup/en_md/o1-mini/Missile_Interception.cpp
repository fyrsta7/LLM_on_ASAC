#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int N;
    cin >> N;
    vector<pair<ll, ll>> missiles(N);
    for(int i=0;i<N;i++) cin >> missiles[i].first >> missiles[i].second;
    vector<ll> d1(N), d2(N);
    for(int i=0;i<N;i++){
        ll dx1 = missiles[i].first - x1;
        ll dy1 = missiles[i].second - y1;
        d1[i] = dx1*dx1 + dy1*dy1;
        ll dx2 = missiles[i].first - x2;
        ll dy2 = missiles[i].second - y2;
        d2[i] = dx2*dx2 + dy2*dy2;
    }
    vector<int> idx(N);
    for(int i=0;i<N;i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](const int a, const int b) -> bool{
        if(d1[a] != d1[b]) return d1[a] < d1[b];
        return d2[a] < d2[b];
    });
    vector<ll> sorted_d2(N);
    for(int i=0;i<N;i++) sorted_d2[i] = d2[idx[i]];
    vector<ll> suffix_max(N, 0);
    if(N > 0){
        suffix_max[N-1] = sorted_d2[N-1];
        for(int i=N-2;i>=0;i--){
            suffix_max[i] = max(suffix_max[i+1], sorted_d2[i]);
        }
    }
    ll min_cost = LLONG_MAX;
    for(int i=0;i<=N;i++){
        ll r1_sq = (i > 0) ? d1[idx[i-1]] : 0;
        ll r2_sq = (i < N) ? suffix_max[i] : 0;
        ll cost = r1_sq + r2_sq;
        if(cost < min_cost) min_cost = cost;
    }
    cout << min_cost;
}