#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    ll a_k, b_k;
    cin >> a_k >> b_k;
    vector<pair<ll, ll>> ministers(n);
    for(int i=0;i<n;i++) cin >> ministers[i].first >> ministers[i].second;
    // Binary search
    ll lo=0, hi=1000000000;
    auto check = [&](ll x) -> bool{
        // Sort ministers by ascending a_i
        vector<pair<ll, ll>> sorted = ministers;
        sort(sorted.begin(), sorted.end(), [&](const pair<ll,ll> &a, const pair<ll,ll> &b) -> bool{
            if(a.first != b.first) return a.first < b.first;
            return a.second > b.second;
        });
        ll P = a_k;
        for(auto &[a, b]: sorted){
            if(P < (x+1)*b){
                if(P > 100000000000000LL / a){
                    // To prevent overflow
                    P = 100000000000000LL;
                }
                else{
                    P *= a;
                }
            }
            else return false;
        }
        return true;
    };
    while(lo < hi){
        ll mid = lo + (hi - lo)/2;
        if(check(mid)) hi = mid;
        else lo = mid +1;
    }
    cout << lo;
}