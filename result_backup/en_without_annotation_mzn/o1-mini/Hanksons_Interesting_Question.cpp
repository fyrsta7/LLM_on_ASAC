#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<tuple<ll, ll, ll, ll>> data(n);
    for(auto &x:data) cin >> get<0>(x) >> get<1>(x) >> get<2>(x) >> get<3>(x);
    vector<int> p(n,0);
    for(int i=0;i<n;i++){
        ll A, G, B, L;
        tie(A, G, B, L) = data[i];
        if(G > A || L % B != 0) { p[i]=0; continue;}
        // x must be multiple of G and divisor of L
        // x = G * k, and G*k divides L => k divides L/G
        if(L % G !=0){ p[i]=0; continue;}
        ll L_div_G = L / G;
        // Now, x = G * k, k divides L_div_G
        // Also, LCM(B, x) = L => LCM(B, G*k) = L
        // LCM(B, G*k) = (B * G * k) / GCD(B, G*k) = L
        // So (B * G * k) / GCD(B, G*k) = L
        // Simplifies to (B * k) / GCD(B, k) = L / G
        // Let's denote M = L / G
        if(L_div_G ==0){ p[i]=0; continue;}
        if(L % G !=0){ p[i]=0; continue;}
        ll M = L_div_G;
        // Now, find k | M, and (B * k) / gcd(B,k) = M
        // Which implies LCM(B,k) = M
        // Also, GCD(A, G*k) = G
        // Which implies GCD(A, k) =1
        // So conditions:
        // 1. k divides M
        // 2. LCM(B,k) = M
        // 3. GCD(A,k) =1
        // Enumerate all divisors of M
        vector<ll> divisors;
        for(ll d=1; d*d <=M; d++){
            if(M%d ==0){
                divisors.push_back(d);
                if(d != M/d) divisors.push_back(M/d);
            }
        }
        for(auto k:divisors){
            ll x = G * k;
            // Check LCM(B, x) = L
            // LCM(B, x) = (B * x)/gcd(B,x) = (B * G *k)/gcd(B, G*k) = L
            // Which is equivalent to LCM(B,k*G) = M*G
            // Already simplified to LCM(B,k) = M
            // So directly check LCM(B,k) == M
            // Also check GCD(A, x) = G, which means GCD(A, G*k) = G => GCD(A/G, k) =1
            if((B * k)/gcd(B, k) != M) continue;
            if(gcd(A, k) !=1) continue;
            p[i]++;
        }
    }
    for(int i=0;i<n;i++) cout << p[i] << (i<n-1?" ":"\n");
}