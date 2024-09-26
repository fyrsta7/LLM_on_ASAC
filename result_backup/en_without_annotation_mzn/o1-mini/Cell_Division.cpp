#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to factorize a number and return vector of pairs (prime, exponent)
vector<pair<ll, ll>> factorize(ll n){
    vector<pair<ll, ll>> factors;
    // Handle 2 separately
    if(n % 2 == 0){
        ll cnt =0;
        while(n %2 ==0){
            cnt++;
            n /=2;
        }
        factors.emplace_back(2, cnt);
    }
    // Check odd numbers
    for(ll i=3;i*i<=n;i+=2){
        if(n%i ==0){
            ll cnt=0;
            while(n%i ==0){
                cnt++;
                n /=i;
            }
            factors.emplace_back(i, cnt);
        }
    }
    if(n >1){
        factors.emplace_back(n,1);
    }
    return factors;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, m1, m2;
    cin >> N >> m1 >> m2;
    vector<ll> S(N);
    for(auto &x:S) cin>>x;
    ll M = pow(m1, m2); // Not used
    const ll max_T = 10000;
    // Factorize m1
    vector<pair<ll, ll>> m1_factors = factorize(m1);
    // Edge case: if m1 ==1, then m1^m2=1, which divides any S[i]^t, so t=1 for all
    if(m1 ==1){
        // ans =1
        cout<<1;
        return 0;
    }
    ll ans = max_T;
    for(auto s:S){
        bool ok = true;
        ll t_i = 0;
        for(auto &[p, a_p]: m1_factors){
            ll b_p =0;
            ll temp = s;
            while(temp %p ==0){
                b_p++;
                temp /=p;
            }
            if(b_p ==0){
                ok = false;
                break;
            }
            // Compute ceil(a_p * m2 / b_p)
            ll numerator = a_p * m2;
            ll t_p = (numerator + b_p -1)/b_p;
            t_i = max(t_i, t_p);
            if(t_i > max_T){
                break;
            }
        }
        if(ok && t_i <= max_T){
            ans = min(ans, t_i);
        }
    }
    if(ans == max_T){
        cout<<-1;
    }
    else{
        cout<<ans;
    }
}