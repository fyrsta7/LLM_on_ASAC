#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> T(n);
    for(auto &x:T) cin >> x;
    sort(T.begin(), T.end());
    long long sum = 0;
    long long last_departure = -1e18;
    for(int i=0;i<n;i++){
        long long departure = max((long long)T[i], last_departure + m);
        sum += departure - T[i];
        last_departure = departure;
    }
    cout << sum;
}