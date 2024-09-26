#include<bits/stdc++.h>
using namespace std;

struct State {
    int step;
    int x, y;
    int last_pick;
    long long value;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int M, N, K;
    cin >> M >> N >> K;
    vector<vector<int>> peanuts(M, vector<int>(N, 0));
    for(int i=0;i<M;i++) {
        for(int j=0; j<N; j++) cin>>peanuts[i][j];
    }
    // Directions: up, down, left, right, pick, wait
    // Represent actions as integers 0 to 5
    // We need to enforce first action is down and last is up
    // BFS with DP: step, x, y, last_pick
    // To maximize value, use DP[step][x][y][last_pick] = max value
    // last_pick can be up to max peanut value
    // To optimize, use memoization with step, x, y, last_pick
    // Assuming M,N,K <= 50 and peanut <=1000
    // Initialize DP
    // Using vector of vectors of vectors
    // To reduce state, last_pick can be from 0 to max_peanut
    int max_peanut = 0;
    for(auto &row: peanuts) for(auto &val: row) max_peanut = max(max_peanut, val);
    // Initialize DP table
    // dp[step][x][y][last_pick] = max value
    // To save memory, use two layers
    // Current and next
    const int INF = -1e18;
    vector<vector<vector<long long>>> dp_prev(M, vector<vector<long long>>(N, vector<long long>(max_peanut+1, INF)));
    // Starting position is (0,0) with last_pick = max_peanut+1 (no pick yet)
    // But to simplify, set last_pick = max_peanut+1 as a virtual start
    // Instead, use last_pick = max_peanut+1 as an initial state
    // However, to keep it simple, assume last_pick = max_peanut +1 is not stored, and allow any first pick
    // Start after first action which is down
    // First action must be down, so from (0,0) to (1,0)
    if(M <=1){
        // Cannot move down
        cout << "0";
        return 0;
    }
    dp_prev[1][0][0] = 0; // At step 1, position (1,0), value 0
    for(int step=1; step<K; step++){
        vector<vector<vector<long long>>> dp_next(M, vector<vector<long long>>(N, vector<long long>(max_peanut+1, INF)));
        for(int x=0; x<M; x++) {
            for(int y=0; y<N; y++) {
                for(int last=0; last<=max_peanut; last++) {
                    if(dp_prev[x][y][last] == INF) continue;
                    long long current = dp_prev[x][y][last];
                    // Possible actions: up, down, left, right, pick, wait
                    // Except first and last steps
                    // Check step+1 actions
                    for(int action=0; action<6; action++){
                        // Skip first and last actions
                        if(step ==1 && action !=1) continue; // first action must be down
                        if(step == K-1 && action !=0) continue; // last action must be up
                        int nx = x, ny = y;
                        if(action ==0){ // up
                            nx = x-1;
                        }
                        else if(action ==1){ // down
                            nx = x+1;
                        }
                        else if(action ==2){ // left
                            ny = y-1;
                        }
                        else if(action ==3){ // right
                            ny = y+1;
                        }
                        else if(action ==4){ // pick
                            // stay
                        }
                        else if(action ==5){ // wait
                            // stay
                        }
                        // Check bounds
                        if(nx <0 || nx >=M || ny <0 || ny >=N) continue;
                        // Calculate new value and last_pick
                        long long new_val = current;
                        int new_last = last;
                        if(action ==4){ // pick
                            if(peanuts[nx][ny] ==0) continue;
                            if(peanuts[nx][ny] > last) continue;
                            new_val += peanuts[nx][ny];
                            new_last = peanuts[nx][ny];
                        }
                        // Update dp_next
                        dp_next[nx][ny][new_last] = max(dp_next[nx][ny][new_last], new_val);
                    }
                }
            }
        }
        dp_prev = move(dp_next);
    }
    // Last action must be up, so position must end at (0,0)
    // So at step K, position must be (0,0)
    // Find the maximum value among all possible last_picks leading to (0,0)
    long long res = INF;
    for(int last=0; last<=max_peanut; last++) {
        res = max(res, dp_prev[0][0][last]);
    }
    if(res == INF) res =0;
    cout << res;
}