#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> h(N);
    for(int &x:h) cin >> x;
    vector<int> t(N);
    for(int i=0;i<N;i++) t[i] = (i < N-1)? h[i+1] : h[0];
    // Create extended h and t
    int M = 2*N;
    vector<int> h_ext(M), t_ext(M);
    for(int i=0;i<M;i++){
        h_ext[i] = h[i%N];
        t_ext[i] = t[i%N];
    }
    // Initialize DP
    // dp[i][j] is the max energy for beads i to j
    // Initialize a 2*N x 2*N table
    // Initialize all to 0
    vector<vector<long long>> dp(M, vector<long long>(M, 0));
    // length from 2 to N
    for(int length=2; length<=N; length++){
        for(int i=0; i+length-1 < M; i++){
            int j = i + length -1;
            dp[i][j] = 0;
            for(int k=i; k<j; k++){
                long long temp = dp[i][k] + dp[k+1][j] + (long long)h_ext[i] * t_ext[k] * t_ext[j];
                if(temp > dp[i][j]){
                    dp[i][j] = temp;
                }
            }
        }
    }
    // Find the maximum over all possible starting positions
    long long maxE = 0;
    for(int s=0; s<N; s++){
        if(dp[s][s+N-1] > maxE){
            maxE = dp[s][s+N-1];
        }
    }
    cout << maxE;
}