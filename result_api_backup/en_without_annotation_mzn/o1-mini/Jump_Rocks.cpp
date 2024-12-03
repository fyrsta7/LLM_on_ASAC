#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll L, N, M;
    cin >> L >> N >> M;
    vector<ll> D(N);
    for(auto &x:D) cin>>x;
    sort(D.begin(), D.end());
    ll low=0, high=L, res=0;
    auto check = [&](ll d) -> bool {
        ll count=0;
        ll last = -d;
        for(auto x:D){
            if(x >= last + d && x >= d && x <= L - d){
                count++;
                last = x;
                if(count >= N - M) break;
            }
        }
        return count >= N - M;
    };
    while(low <= high){
        ll mid = low + (high - low)/2;
        if(check(mid)){
            res = mid;
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    cout << "mindist=" << res;
}