#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> grid(n, vector<int>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> grid[i][j];
        }
    }
    // Total states: (n*m) * (n*m) <= 900*900=810000
    const int MAX_STATE = 900*900;
    vector<int> visited(n*m*n*m, 0);
    int current_query = 1;
    // Directions: up, down, left, right
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};
    // Precompute valid moves for each position
    // Not necessary, handle during BFS
    while(q--){
        int EX, EY, SX, SY, TX, TY;
        cin >> EX >> EY >> SX >> SY >> TX >> TY;
        // Convert to 0-based
        EX--; EY--;
        SX--; SY--;
        TX--; TY--;
        if(SX == TX && SY == TY){
            cout << "0\n";
            continue;
        }
        // Check if target and goal are movable
        if(grid[SX][SY]==0 || grid[TX][TY]==0){
            cout << "-1\n";
            continue;
        }
        // Initialize BFS
        // State: (tx, ty, bx, by)
        // Map to state_id = (tx * m + ty) * n * m + (bx * m + by)
        int start_state = (SX * m + SY) * n * m + (EX * m + EY);
        // Initialize queue
        queue<int> qBFS;
        qBFS.push(start_state);
        visited[start_state] = current_query;
        bool found = false;
        int moves = 0;
        while(!qBFS.empty()){
            int size = qBFS.size();
            for(int i=0;i<size;i++){
                int state = qBFS.front(); qBFS.pop();
                int tx = state / (n*m) / m;
                int ty = (state / (n*m)) % m;
                int temp = state % (n*m);
                int bx = temp / m;
                int by = temp % m;
                if(tx == TX && ty == TY){
                    cout << moves << "\n";
                    found = true;
                    // Clear the queue for the next query
                    while(!qBFS.empty()) qBFS.pop();
                    break;
                }
                // Try moving the blank in 4 directions
                for(int d=0; d<4; d++){
                    int nbx = bx + dx[d];
                    int nby = by + dy[d];
                    if(nbx <0 || nbx >=n || nby <0 || nby >=m) continue;
                    if(grid[nbx][nby]==0) continue;
                    // Determine new target position
                    int ntx = tx, nty = ty;
                    if(nbx == tx && nby == ty){
                        ntx = bx;
                        nty = by;
                    }
                    // New blank position
                    int new_bx = nbx;
                    int new_by = nby;
                    // Check if the new target position is valid
                    // Already handled by grid
                    // Map to new state
                    int new_state = (ntx * m + nty) * n * m + (new_bx * m + new_by);
                    if(visited[new_state] != current_query){
                        visited[new_state] = current_query;
                        qBFS.push(new_state);
                    }
                }
            }
            if(found) break;
            moves++;
        }
        if(!found){
            cout << "-1\n";
        }
        current_query++;
    }
}