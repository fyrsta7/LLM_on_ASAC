#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<ll> coefficient(n+1);
    for(auto &x : coefficient) cin >> x;
    vector<int> solutions;
    for(int i=1;i<=m;i++){
        ll val = 0;
        for(int j = n; j >=0; j--){
            val = val * i + coefficient[j];
            if(abs(val) > 1e18) break;
        }
        if(val == 0) solutions.push_back(i);
    }
    cout << solutions.size() << "\n";
    for(auto x : solutions) cout << x << "\n";
}