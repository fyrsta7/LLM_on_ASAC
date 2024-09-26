#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ll k, w;
    cin >> k >> w;
    ll scale = 1LL << k;
    ll maxnum = (w >= 64) ? LLONG_MAX : (1LL << w);
    ll n = scale -1;
    ll total =0;
    for(ll l=2;l<=w;l++){
        if(l > n) break;
        // Compute C(n, l)
        ll C=1;
        for(ll i=1;i<=l;i++){
            if (C > maxnum) {C = maxnum +1; break;}
            C = C * (n - i +1)/i;
        }
        total += C;
        if(total >= maxnum){
            total = maxnum;
            break;
        }
    }
    ll optnum = min(total, maxnum -1);
    cout << optnum;
}