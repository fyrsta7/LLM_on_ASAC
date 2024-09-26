#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> initial_board(n, vector<int>(m));
    int movable = 0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> initial_board[i][j];
            if(initial_board[i][j]==1) movable++;
        }
    }
    int max_steps = movable * movable;
    struct Query{
        int l1x, l1y, l2x, l2y, fx, fy;
    };
    vector<Query> queries(q);
    for(int i=0;i<q;i++) cin >> queries[i].l1x >> queries[i].l1y >> queries[i].l2x >> queries[i].l2y >> queries[i].fx >> queries[i].fy;
    // Directions: up, down, left, right
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};
    for(int i=0;i<q;i++){
        // Initialize board
        vector<vector<int>> board = initial_board;
        int l1x = queries[i].l1x-1, l1y = queries[i].l1y-1;
        int l2x = queries[i].l2x-1, l2y = queries[i].l2y-1;
        int fx = queries[i].fx-1, fy = queries[i].fy-1;
        board[l1x][l1y] = -1;
        board[l2x][l2y] = 2;
        // Serialize board
        auto serialize = [&](const vector<vector<int>>& b) -> string{
            string s;
            for(auto &row: b){
                for(auto &val: row) s += to_string(val)+",";
            }
            return s;
        };
        string start = serialize(board);
        // BFS
        unordered_set<string> visited;
        queue<pair<string, int>> q_bfs;
        q_bfs.push({start, 0});
        visited.insert(start);
        bool found = false;
        int res = -1;
        while(!q_bfs.empty()){
            auto [state, steps] = q_bfs.front(); q_bfs.pop();
            if(steps > max_steps) break;
            // Deserialize state
            vector<vector<int>> current(n, vector<int>(m));
            int idx = 0;
            int pos_x, pos_y;
            string num;
            for(int x=0;x<n;x++) {
                for(int y=0;y<m;y++) {
                    if(state[idx]==','){
                        // Should not happen
                    }
                    size_t comma = state.find(',', idx);
                    num = state.substr(idx, comma - idx);
                    current[x][y] = stoi(num);
                    if(current[x][y]==-1){
                        pos_x = x;
                        pos_y = y;
                    }
                    idx = comma +1;
                }
            }
            // Check if target is achieved
            if(current[fx][fy]==2){
                res = steps;
                found = true;
                break;
            }
            if(steps == max_steps) continue;
            // Try all moves
            for(int d=0;d<4;d++){
                int nx = pos_x + dx[d];
                int ny = pos_y + dy[d];
                if(nx >=0 && nx <n && ny >=0 && ny <m && current[nx][ny] !=0){
                    // Swap
                    vector<vector<int>> next_board = current;
                    next_board[pos_x][pos_y] = next_board[nx][ny];
                    next_board[nx][ny] = -1;
                    string next_state = serialize(next_board);
                    if(!visited.count(next_state)){
                        visited.insert(next_state);
                        q_bfs.push({next_state, steps+1});
                    }
                }
            }
        }
        if(found && res <= max_steps){
            cout << res << "\n";
        }
        else{
            cout << "-1\n";
        }
    }
}