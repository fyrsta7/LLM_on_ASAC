#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

struct Plant {
    int i;
    int j;
    int P;
};

int main(){
    int M, N, K;
    cin >> M >> N >> K;
    vector<vector<int>> grid(M, vector<int>(N, 0));
    vector<Plant> plants;
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            cin >> grid[i][j];
            if(grid[i][j]>0){
                plants.push_back(Plant{ i+1, j+1, grid[i][j]});
            }
        }
    }
    int S = plants.size();
    if(S ==0){
        cout << "0";
        return 0;
    }
    // Precompute sum_P for each mask
    int size = 1<<S;
    vector<int> sum_P(size, 0);
    for(int mask=1; mask<size; mask++){
        int lsb = mask & -mask;
        int idx = __builtin_ctz(lsb);
        sum_P[mask] = sum_P[mask ^ lsb] + plants[idx].P;
    }
    // Precompute distances
    vector<vector<int>> dist(S, vector<int>(S, 0));
    for(int u=0; u<S; u++) {
        for(int v=0; v<S; v++) {
            dist[u][v] = abs(plants[u].i - plants[v].i) + abs(plants[u].j - plants[v].j);
        }
    }
    // Distance from roadside to each plant
    vector<int> roadside_to(S, 0);
    for(int u=0; u<S; u++) {
        roadside_to[u] = plants[u].i -1;
    }
    // Initialize DP
    const int INF = INT32_MAX;
    vector<vector<int>> DP(1<<S, vector<int>(S, INF));
    for(int u=0; u<S; u++) {
        int mask = 1<<u;
        DP[mask][u] = 1 + roadside_to[u] +1; // jump + move + pick
    }
    // DP
    for(int mask=1; mask<(1<<S); mask++) {
        for(int u=0; u<S; u++) {
            if(!(mask & (1<<u))) continue;
            if(DP[mask][u] == INF) continue;
            for(int v=0; v<S; v++) {
                if(mask & (1<<v)) continue;
                int new_mask = mask | (1<<v);
                int new_time = DP[mask][u] + dist[u][v] +1; // move + pick
                if(new_time < DP[new_mask][v]){
                    DP[new_mask][v] = new_time;
                }
            }
        }
    }
    // Find maximum sum_P with time + return_time <=K
    int max_P =0;
    for(int mask=1; mask<(1<<S); mask++) {
        for(int u=0; u<S; u++) {
            if(!(mask & (1<<u))) continue;
            if(DP[mask][u] == INF) continue;
            int total_time = DP[mask][u] + (plants[u].i -1) +1; // return move + jump
            if(total_time <= K){
                if(sum_P[mask] > max_P){
                    max_P = sum_P[mask];
                }
            }
        }
    }
    cout << max_P;
}
