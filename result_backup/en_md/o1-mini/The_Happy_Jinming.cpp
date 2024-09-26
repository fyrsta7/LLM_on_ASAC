#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, m;
    cin >> N >> m;
    int v, p;
    int dp_size = N + 1;
    long long dp[30001];
    for(int i=0;i<=N;i++) dp[i]=0;
    for(int i=0;i<m;i++){
        cin >> v >> p;
        long long val = (long long)v * p;
        for(int j=N; j>=v; j--){
            if(dp[j - v] + val > dp[j]){
                dp[j] = dp[j - v] + val;
            }
        }
    }
    long long result = 0;
    for(int i=0;i<=N;i++) if(dp[i] > result) result = dp[i];
    cout << result;
}