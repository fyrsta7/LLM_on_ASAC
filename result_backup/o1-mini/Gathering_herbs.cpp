#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int T, M;
    cin >> T >> M;
    vector<pair<int, int>> herbs(M);
    for(int i=0;i<M;i++) cin >> herbs[i].first >> herbs[i].second;
    vector<int> dp(T+1, 0);
    for(int i=0;i<M;i++){
        int time = herbs[i].first;
        int value = herbs[i].second;
        for(int j=T; j>=time; j--){
            if(dp[j - time] + value > dp[j]){
                dp[j] = dp[j - time] + value;
            }
        }
    }
    int maxVal = 0;
    for(int i=0;i<=T;i++) if(dp[i] > maxVal) maxVal = dp[i];
    cout << maxVal;
}