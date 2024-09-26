#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    ll a, b;
    ll min_cost = LLONG_MAX;
    for(int i=0;i<3;i++){
        cin >> a >> b;
        ll needed = (n + a -1)/a;
        ll cost = needed * b;
        if(cost < min_cost){
            min_cost = cost;
        }
    }
    cout << "cost=" << min_cost;
}