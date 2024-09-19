#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> head(N), tail(N);
    
    for (int i = 0; i < N; ++i) {
        head[i] = i == 0 ? 2 : head[i - 1];
        tail[i] = (i + 1 == N) ? head[0] : head[i + 1];
    }
    
    vector<vector<long long>> dp(N, vector<long long>(N, 0));
    vector<vector<int>> length(N, vector<int>(N, 0));
    
    for (int len = 1; len <= N; ++len) {
        for (int i = 0; i < N; ++i) {
            int j = (i + len - 1) % N;
            if (len == 1) {
                length[i][j] = head[i];
                dp[i][j] = 0;
            } else {
                for (int k = 1; k < len; ++k) {
                    int mid = (i + k) % N;
                    long long energy = dp[i][mid] + dp[mid][j] + head[i] * tail[mid] * head[j];
                    if (energy > dp[i][j]) {
                        dp[i][j] = energy;
                        length[i][j] = tail[mid];
                    }
                }
            }
        }
    }
    
    cout << dp[0][N - 1] << endl;
    
    return 0;
}