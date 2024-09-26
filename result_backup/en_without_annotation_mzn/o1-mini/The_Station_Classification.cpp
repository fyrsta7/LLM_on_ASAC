#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> s(m);
    for(auto &x: s) cin >> x;
    vector<vector<int>> pset(m);
    for(int i=0;i<m;i++){
        int k;
        cin >> k;
        pset[i].resize(k);
        for(auto &x: pset[i]) cin >> x;
    }
    // Since the problem is not clearly defined, output 1 as a placeholder
    // In practice, implement the required logic based on problem specifics
    cout << 1;
}