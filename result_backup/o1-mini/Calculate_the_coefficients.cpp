#include <iostream>
using namespace std;

typedef long long ll;

const int MOD = 10007;

ll power_mod(ll base, int exp) {
    ll res = 1;
    base %= MOD;
    while(exp > 0){
        if(exp & 1){
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

int main(){
    int a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;
    if(n + m != k){
        cout << 0;
        return 0;
    }
    // Compute C(k, m) using 1D DP
    int C[1001] = {0};
    C[0] = 1;
    for(int i=1;i<=k;i++){
        for(int j=i; j>=1; j--){
            C[j] = (C[j] + C[j-1]) % MOD;
        }
    }
    if(m > k){
        cout << 0;
        return 0;
    }
    int comb = C[m];
    ll a_pow = power_mod(a, n);
    ll b_pow = power_mod(b, m);
    ll result = (comb * a_pow) % MOD;
    result = (result * b_pow) % MOD;
    cout << result;
}