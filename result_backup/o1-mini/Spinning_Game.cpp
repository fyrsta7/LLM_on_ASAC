#include <iostream>
using namespace std;

typedef long long ll;

ll powmod_func(ll a, ll b, ll mod){
    if(mod == 1) return 0;
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>=1;
    }
    return res;
}

int main(){
    ll n, m, k, x;
    cin >> n >> m >> k >> x;
    ll t;
    if(n ==0){
        t =0;
    }
    else{
        t = powmod_func(10, k, n);
    }
    ll ans = (x + ((m % n) * t) ) % n;
    cout << ans;
}