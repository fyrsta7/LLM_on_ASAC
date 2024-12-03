#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long long> d(n);
    for(auto &x: d) cin >> x;
    long long ans=0;
    long long prev=0;
    for(int i=0;i<n;i++){
        if(d[i]>prev){
            ans += d[i]-prev;
        }
        prev = d[i];
    }
    cout << ans;
}