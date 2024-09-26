#include<bits/stdc++.h>
using namespace std;

long long extended_gcd(long long a, long long b, long long& x, long long& y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long a, b;
    cin >> a >> b;
    long long x, y;
    long long g = extended_gcd(a, b, x, y);
    // Assuming gcd(a,b) ==1
    long long res = x % b;
    if(res <=0) res += b;
    cout << res;
}