#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> grid(N, vector<int>(M));
    for(auto &row:grid) for(auto &cell:row) cin >> cell;
    // Identify storage plants (row 0)
    vector<int> storage_cols;
    for(int j=0;j<M;j++) storage_cols.push_back(j);
    int num_storage = storage_cols.size();
    // Identify last row cells
    vector<int> last_cols;
    for(int j=0;j<M;j++) last_cols.push_back(j);
    int num_last = last_cols.size();
    // Assign indices to last row cells
    // Map from (N-1, j) to index
    // Precompute for each storage plant the last row cells it can reach
    vector<bitset<1000>> cover(num_storage, bitset<1000>());
    // Directions: up, down, left, right
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    for(int s=0;s<num_storage;s++){
        int cj = storage_cols[s];
        // BFS from (0, cj)
        vector<vector<bool>> visited(N, vector<bool>(M, false));
        queue<pair<int,int>> q;
        q.push({0, cj});
        visited[0][cj] = true;
        while(!q.empty()){
            pair<int,int> current = q.front(); q.pop();
            int i = current.first, j = current.second;
            // If it's in last row, mark it
            if(i == N-1){
                int idx = j;
                cover[s].set(idx);
            }
            // Explore neighbors with lower altitude
            for(int d=0; d<4; d++){
                int ni = i + dirs[d][0];
                int nj = j + dirs[d][1];
                if(ni >=0 && ni < N && nj >=0 && nj < M && !visited[ni][nj]){
                    if(grid[ni][nj] < grid[i][j]){
                        visited[ni][nj] = true;
                        q.push({ni, nj});
                    }
                }
            }
        }
    }
    // Now, for each last row cell, check if it's covered by any storage plant
    bool possible = true;
    int uncovered = 0;
    // Number of last row cells is M
    for(int j=0; j<M; j++){
        bool covered = false;
        for(int s=0; s<num_storage; s++) if(cover[s].test(j)){ covered = true; break;}
        if(!covered){ uncovered++; }
    }
    if(uncovered >0){
        cout << "0\n" << uncovered;
        return 0;
    }
    // Now, all last row cells can be covered. Find minimal number of storage plants
    // Implement set cover via backtracking
    // Use bitset to represent covered
    bitset<1000> full;
    for(int j=0; j<M; j++) full.set(j);
    int min_count = num_storage;
    // Sort storage plants by the number of last row cells they cover, descending
    vector<int> order(num_storage);
    for(int s=0;s<num_storage;s++) order[s] = s;
    sort(order.begin(), order.end(), [&](const int a, const int b) -> bool{
        return cover[a].count() > cover[b].count();
    });
    // Recursive backtracking
    function<void(int, bitset<1000>, int)> dfs = [&](int idx, bitset<1000> current, int count) {
        if(current == full){
            if(count < min_count) min_count = count;
            return;
        }
        if(idx == num_storage) return;
        if(count >= min_count) return;
        // Estimate the lower bound
        int remaining = (full ^ current).count();
        int max_cover = 0;
        for(int i=idx;i<num_storage;i++) max_cover = max(max_cover, (int)( (cover[order[i]] & (~current)).count()));
        if(max_cover ==0) return;
        if(count +1 >= min_count) return;
        // Choose the current storage plant
        dfs(idx+1, current | cover[order[idx]], count+1);
        // Do not choose the current storage plant
        dfs(idx+1, current, count);
    };
    bitset<1000> initial;
    dfs(0, initial, 0);
    cout << "1\n" << min_count;
}