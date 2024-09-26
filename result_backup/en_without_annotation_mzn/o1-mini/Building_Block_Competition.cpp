#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> h(n);
    for(auto &x:h) cin>>x;
    long long actions = h[0];
    for(int i=1;i<n;i++) actions += max(0, h[i]-h[i-1]);
    cout<<actions;
}