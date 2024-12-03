#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> board(n, vector<int>(m, 0));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> board[i][j];
        }
    }
    // Precompute fixed cells
    // Read queries
    // Prepare visited array
    int total_states = n * m * n * m;
    vector<int> visited(total_states, 0);
    int query_id = 1;
    // Directions: up, down, left, right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    while(q--){
        int EX, EY, SX, SY, TX, TY;
        cin >> EX >> EY >> SX >> SY >> TX >> TY;
        // Convert to 0-based
        int blank_x = EX -1;
        int blank_y = EY -1;
        int piece_x = SX -1;
        int piece_y = SY -1;
        int target_x = TX -1;
        int target_y = TY -1;
        // Check if initial piece is already at target
        if(piece_x == target_x && piece_y == target_y){
            cout << "0\n";
            query_id++;
            continue;
        }
        // Encode initial state
        // state = (blank_x * m + blank_y) + (piece_x * m + piece_y) * n * m
        int initial_state = (blank_x * m + blank_y) + (piece_x * m + piece_y) * n * m;
        // Initialize BFS
        queue<int> q_bfs;
        q_bfs.push(initial_state);
        visited[initial_state] = query_id;
        int steps =0;
        bool found = false;
        while(!q_bfs.empty()){
            int size = q_bfs.size();
            for(int s=0;s<size;s++){
                int current = q_bfs.front(); q_bfs.pop();
                // Decode current state
                int cb = current % (n*m);
                int cp = current / (n*m);
                int blank_curr_x = cb / m;
                int blank_curr_y = cb % m;
                int piece_curr_x = cp / m;
                int piece_curr_y = cp % m;
                // Check if piece is at target
                if(piece_curr_x == target_x && piece_curr_y == target_y){
                    cout << steps << "\n";
                    found = true;
                    break;
                }
                // Try all 4 directions
                for(int d=0; d<4; d++){
                    int nx = blank_curr_x + dx[d];
                    int ny = blank_curr_y + dy[d];
                    if(nx <0 || nx >=n || ny <0 || ny >=m) continue;
                    if(board[nx][ny] ==0) continue;
                    // Determine new blank and piece positions
                    int new_blank_x = nx;
                    int new_blank_y = ny;
                    int new_piece_x = piece_curr_x;
                    int new_piece_y = piece_curr_y;
                    if(nx == piece_curr_x && ny == piece_curr_y){
                        new_piece_x = blank_curr_x;
                        new_piece_y = blank_curr_y;
                    }
                    // Encode new state
                    int new_cb = new_blank_x * m + new_blank_y;
                    int new_cp = new_piece_x * m + new_piece_y;
                    int new_state = new_cb + new_cp * n * m;
                    if(visited[new_state] != query_id){
                        visited[new_state] = query_id;
                        q_bfs.push(new_state);
                    }
                }
            }
            if(found) break;
            steps++;
        }
        if(!found){
            // After BFS, check if piece is at target
            // It was checked inside BFS
            cout << "-1\n";
        }
        query_id++;
    }
}