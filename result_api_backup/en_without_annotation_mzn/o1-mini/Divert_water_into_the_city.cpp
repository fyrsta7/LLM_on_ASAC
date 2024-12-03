#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> height(N, vector<int>(M));
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cin >> height[i][j];
        }
    }
    // For each first-row cell, find which last-row columns it can reach
    vector<bitset<1000>> reach(M, bitset<1000>()); // Assuming M <=1000
    for(int j=0; j<M; j++){
        // BFS from (0, j)
        vector<vector<bool>> visited(N, vector<bool>(M, false));
        queue<pair<int, int>> q;
        q.push({0, j});
        visited[0][j] = true;
        while(!q.empty()){
            pair<int, int> current = q.front(); q.pop();
            int x = current.first, y = current.second;
            if(x == N-1){
                reach[j].set(y);
            }
            // Directions: up, down, left, right
            vector<pair<int,int>> dirs = { {x-1, y}, {x+1, y}, {x, y-1}, {x, y+1} };
            for(auto &dir: dirs){
                int nx = dir.first, ny = dir.second;
                if(nx >=0 && nx < N && ny >=0 && ny < M && !visited[nx][ny]){
                    if(height[nx][ny] <= height[x][y]){
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }
    }
    // Greedy Set Cover
    bitset<1000> covered;
    int stores = 0;
    while(covered.count() < M){
        int best = -1;
        int best_cover = -1;
        for(int j=0; j<M; j++){
            if(reach[j].count() ==0) continue;
            // Calculate how many new columns this store can cover
            bitset<1000> new_cover = reach[j] & (~covered);
            int cnt = new_cover.count();
            if(cnt > best_cover){
                best_cover = cnt;
                best = j;
            }
        }
        if(best == -1){
            break;
        }
        covered |= reach[best];
        stores++;
    }
    if(covered.count() == M){
        cout << "1\n" << stores;
    }
    else{
        cout << "0\n" << M - (int)covered.count();
    }
}