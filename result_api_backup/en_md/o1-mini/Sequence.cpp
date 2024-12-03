#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main(){
    int k, N;
    cin >> k >> N;
    int m=15;
    vector<ll> powers(m,1);
    for(int i=1;i<m;i++) powers[i]=powers[i-1]*k;
    vector<ll> sums;
    sums.reserve(32768);
    for(int mask=1; mask<(1<<m); mask++){
        ll s=0;
        for(int i=0;i<m;i++) if(mask & (1<<i)) s += powers[i];
        sums.push_back(s);
    }
    sort(sums.begin(), sums.end());
    cout << sums[N-1];
}