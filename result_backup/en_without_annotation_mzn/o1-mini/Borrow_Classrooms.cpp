#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<long long> r(n);
    for(auto &x: r) cin>>x;
    vector<long long> d(m), s(m), t(m);
    for(int i=0;i<m;i++) cin>>d[i];
    for(int i=0;i<m;i++) cin>>s[i];
    for(int i=0;i<m;i++) cin>>t[i];
    // Binary search
    int low=0, high=m;
    while(low < high){
        int mid = low + (high - low +1)/2;
        // Compute sum_d[j] using difference array
        vector<long long> temp(n+1, 0);
        for(int i=0;i<mid;i++){
            temp[s[i]-1] += d[i];
            if(t[i] < n) temp[t[i]] -= d[i];
        }
        bool ok=true;
        long long curr=0;
        for(int j=0;j<n;j++){
            curr += temp[j];
            if(curr > r[j]){
                ok=false;
                break;
            }
        }
        if(ok) low=mid;
        else high=mid-1;
    }
    if(low == m){
        cout << "0";
    }
    else{
        cout << "-1\n" << (low+1);
    }
}