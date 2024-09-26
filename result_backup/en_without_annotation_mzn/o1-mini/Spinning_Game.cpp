#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll powmod(ll base, ll exponent, ll mod){
    ll result = 1;
    base %= mod;
    while(exponent > 0){
        if(exponent & 1){
            result = (__int128(result) * base) % mod;
        }
        base = (__int128(base) * base) % mod;
        exponent >>= 1;
    }
    return result;
}

int main(){
    ll n, m, k, x;
    cin >> n >> m >> k >> x;
    ll rounds_mod = powmod(10, k, n);
    ll state = (x % n + (__int128(m) * rounds_mod) % n) % n;
    cout << state;
}