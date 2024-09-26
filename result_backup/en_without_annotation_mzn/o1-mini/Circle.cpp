#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ll n, k;
    cin >> n >> k;
    if(k <0){
        cout << "-1";
        return 0;
    }
    ll mod = 1;
    for(int i=0;i<k;i++) mod *=10;
    if(mod ==0) mod =1;
    ll suffix1 = n % mod;
    ll current_power = suffix1;
    ll len = mod;
    bool found = false;
    ll result = -1;
    for(ll i=2;i<=len;i++){
        current_power = (current_power * n) % mod;
        if(current_power == suffix1){
            result = i-1;
            found = true;
            break;
        }
    }
    cout << (found ? to_string(result) : "-1");
}