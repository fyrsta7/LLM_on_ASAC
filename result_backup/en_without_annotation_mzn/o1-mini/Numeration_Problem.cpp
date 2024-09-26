#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll count_digit(ll n, int x){
    if(n <0)return 0;
    ll count =0;
    ll factor =1;
    while(factor <=n){
        ll lower = n % factor;
        ll curr = (n / factor) %10;
        ll higher = n / (factor *10);
        if(curr >x){
            count += (higher +1)*factor;
        }
        else if(curr ==x){
            count += higher * factor + lower +1;
        }
        else{
            count += higher * factor;
        }
        if(x ==0){
            count -= factor;
        }
        factor *=10;
    }
    return count;
}

int main(){
    ll n;
    int x;
    cin>>n>>x;
    cout<<count_digit(n, x);
}