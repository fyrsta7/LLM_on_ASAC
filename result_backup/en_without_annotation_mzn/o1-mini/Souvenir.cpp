#include<bits/stdc++.h>
using namespace std;

int main(){
    int T, N, M;
    cin>>T>>N>>M;
    vector<vector<int>> P(T, vector<int>(N));
    for(auto &row:P) for(auto &x:row) cin>>x;
    // Initialize coins and holdings
    long long coin = M;
    vector<long long> hold(N, 0);
    for(int i=0;i<T;i++){
        // Decide to sell first
        for(int j=0;j<N;j++){
            // Check if future price is higher
            int future_max = 0;
            for(int k=i+1;k<T;k++) future_max = max(future_max, P[k][j]);
            if(P[i][j] < future_max && hold[j]>0){
                // Sell all
                coin += hold[j]*P[i][j];
                hold[j]=0;
            }
        }
        // Decide to buy
        // Calculate potential profit
        vector<pair<int, int>> profit;
        for(int j=0;j<N;j++){
            int future_max = 0;
            for(int k=i+1;k<T;k++) future_max = max(future_max, P[k][j]);
            if(P[i][j] < future_max){
                profit.emplace_back(future_max - P[i][j], j);
            }
        }
        // Sort by profit descending
        sort(profit.begin(), profit.end(), [&](pair<int,int> a, pair<int,int> b)->bool{
            return a.first > b.first;
        });
        // Buy as much as possible starting from highest profit
        for(auto &[diff, j]: profit){
            if(diff <=0) continue;
            long long can_buy = coin / P[i][j];
            if(can_buy >0){
                hold[j] += can_buy;
                coin -= can_buy * (long long)P[i][j];
            }
        }
    }
    // At the end, sell all holdings
    for(int j=0;j<N;j++) {
        coin += hold[j]*P[T-1][j];
        hold[j]=0;
    }
    cout<<coin;
}