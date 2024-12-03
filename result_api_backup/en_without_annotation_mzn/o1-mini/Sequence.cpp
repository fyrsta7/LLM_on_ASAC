#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ll k, N;
    cin >> k >> N;
    ll ans = 0;
    ll power = 1;
    while(N > 0){
        if(N & 1){
            ans += power;
        }
        power *= k;
        N >>=1;
    }
    cout << ans;
}