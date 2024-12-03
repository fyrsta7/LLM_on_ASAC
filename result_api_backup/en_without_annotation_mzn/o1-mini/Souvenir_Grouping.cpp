#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long w, n;
    cin >> w >> n;
    vector<long long> P(n);
    for(auto &x: P) cin >> x;
    sort(P.begin(), P.end());
    int i=0, j=n-1;
    int count=0;
    while(i <= j){
        if(P[i] + P[j] <= w) i++;
        j--;
        count++;
    }
    cout << count;
}