#include <iostream>
using namespace std;

typedef long long ll;

ll extended_gcd_func(ll a, ll b, ll& x, ll& y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd_func(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main(){
    ll a, b;
    cin >> a >> b;
    ll x, y;
    ll g = extended_gcd_func(a, b, x, y);
    // Since g = 1, inverse exists
    ll inv = (x % b + b) % b;
    cout << inv;
}