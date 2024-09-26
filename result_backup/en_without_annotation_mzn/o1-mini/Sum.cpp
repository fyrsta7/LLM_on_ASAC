#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> color(n+1);
    for(int i=1;i<=n;i++) cin >> color[i];
    vector<int> number(n+1);
    for(int i=1;i<=n;i++) cin >> number[i];
    long long total = 0;
    for(int i=1;i<=n;i++){
        for(int d=1; i + 2*d <=n; d++){
            int k = i + 2*d;
            if(color[i] == color[k]){
                long long term = (long long)(i + k) * ((long long)number[i] + number[k]);
                total += term;
            }
        }
    }
    int res = total % 10007;
    cout << res;
}