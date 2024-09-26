#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll count_twos(ll x){
    ll count =0;
    ll factor=1;
    while(factor <=x){
        ll lower = x % factor;
        ll current = (x / factor) %10;
        ll higher = x / (factor*10);
        if(current <2){
            count += higher * factor;
        }
        else if(current ==2){
            count += higher * factor + lower +1;
        }
        else{
            count += (higher +1)* factor;
        }
        factor *=10;
    }
    return count;
}

int main(){
    ll l, r;
    cin >> l >> r;
    ll answer = count_twos(r) - count_twos(l-1);
    cout << answer;
}