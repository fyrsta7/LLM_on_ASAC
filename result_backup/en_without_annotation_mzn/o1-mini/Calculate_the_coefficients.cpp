#include<bits/stdc++.h>
using namespace std;

const int MOD = 10007;
long long fact[MOD];
long long inv_fact_arr[MOD];

// Fast exponentiation
long long powmod_func(long long a, long long b){
    long long res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

// Compute factorial modulo MOD
void compute_fact(){
    fact[0]=1;
    for(int i=1;i<MOD;i++) fact[i] = fact[i-1]*i%MOD;
}

// Compute inverse factorial modulo MOD using Fermat
void compute_inv_fact(){
    inv_fact_arr[MOD-1] = powmod_func(fact[MOD-1], MOD-2);
    for(int i=MOD-2;i>=0;i--) inv_fact_arr[i] = inv_fact_arr[i+1]*(i+1)%MOD;
}

// Compute C(n,k) mod MOD
long long comb(int n, int k){
    if(k > n) return 0;
    return fact[n] * inv_fact_arr[k] % MOD * inv_fact_arr[n-k] % MOD;
}

// Compute C(n,k) mod MOD using Lucas Theorem
long long lucas(long long n, long long k){
    long long res =1;
    while(n >0 || k >0){
        int ni = n % MOD;
        int ki = k % MOD;
        if(ki > ni) return 0;
        res = res * comb(ni, ki) % MOD;
        n /= MOD;
        k /= MOD;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    compute_fact();
    compute_inv_fact();
    long long a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;
    long long c = lucas(k, n);
    long long term1 = c;
    long long term2 = powmod_func(a, n);
    long long term3 = powmod_func(b, m);
    long long coefficient = term1 * term2 % MOD;
    coefficient = coefficient * term3 % MOD;
    cout << coefficient;
}