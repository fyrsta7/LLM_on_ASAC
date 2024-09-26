#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<vector<int>> color(n+1, vector<int>(n+1));
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            cin >> color[i][j];
        }
    }
    // Initialize distances
    const long long INF = 1e18;
    vector<vector<vector<long long>>> dist(n+1, vector<vector<long long>>(n+1, vector<long long>(2, INF)));
    // Priority queue: (cost, i, j, tc)
    // Use min-heap
    priority_queue<tuple<long long, int, int, int>, vector<tuple<long long, int, int, int>>, std::greater<tuple<long long, int, int, int>>> pq;
    // Initialize starting state
    if(color[1][1] >=0){
        int tc = color[1][1];
        dist[1][1][tc] = 0;
        pq.emplace(0, 1, 1, tc);
    }
    else{
        dist[1][1][0] = 0;
        pq.emplace(0,1,1,0);
        dist[1][1][1] = 0;
        pq.emplace(0,1,1,1);
    }
    // Directions: up, down, left, right
    int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    while(!pq.empty()){
        auto [cost, i, j, tc] = pq.top(); pq.pop();
        if(i ==n && j ==n){
            // Continue to find the minimal
        }
        if(cost > dist[i][j][tc]) continue;
        for(auto &d: dirs){
            int ni = i + d[0];
            int nj = j + d[1];
            if(ni <1 || ni >n || nj <1 || nj >n) continue;
            // Check the constraint: not both current and next cell have color==-1
            if(color[i][j]==-1 && color[ni][nj]==-1) continue;
            // Determine possible ntc
            if(color[ni][nj] >=0){
                int ntc = color[ni][nj];
                // Calculate cost
                long long new_cost = cost + ((tc != ntc) ? 1 : 0) + ((color[ni][nj]==-1)? 2 :0);
                if(new_cost < dist[ni][nj][ntc]){
                    dist[ni][nj][ntc] = new_cost;
                    pq.emplace(new_cost, ni, nj, ntc);
                }
            }
            else{
                for(int ntc=0; ntc<=1; ntc++){
                    // Calculate cost
                    long long new_cost = cost + ((tc != ntc) ? 1 : 0) + 2;
                    if(new_cost < dist[ni][nj][ntc]){
                        dist[ni][nj][ntc] = new_cost;
                        pq.emplace(new_cost, ni, nj, ntc);
                    }
                }
            }
        }
    }
    long long answer = 1e18;
    for(int tc=0; tc<=1; tc++) {
        answer = min(answer, dist[n][n][tc]);
    }
    cout << "ans=" << answer;
}