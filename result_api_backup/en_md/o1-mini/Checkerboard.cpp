#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <tuple>

using namespace std;

struct State {
    int cost;
    int x, y;
    int can_cast;
    int temp_color; // 0,1 for temporary colors, 2 for permanent (-1)
    bool operator<(const State &other) const {
        return cost > other.cost;
    }
};

int main(){
    int m, n;
    cin >> m >> n;
    // Initialize grid to -1 (colorless)
    vector<vector<int>> grid(m+1, vector<int>(m+1, -1));
    for(int i=0;i<n;i++){
        int x, y, c;
        cin >> x >> y >> c;
        grid[x][y] = c;
    }
    // Directions: up, down, left, right
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    // Initialize distance
    // temp_color: 0,1,2 (-1 mapped to 2)
    const int INF = 1e9;
    int distance_grid[101][101][2][3];
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=m;j++) {
            for(int c=0;c<2;c++) {
                for(int t=0;t<3;t++) {
                    distance_grid[i][j][c][t] = INF;
                }
            }
        }
    }
    // Starting state
    int start_color = grid[1][1];
    int start_temp = 2; // permanent
    int start_can_cast =1;
    priority_queue<State> pq;
    State start_state = {0, 1,1,2};
    pq.push(start_state);
    distance_grid[1][1][1][2] =0;
    while(!pq.empty()){
        State current = pq.top(); pq.pop();
        int cost = current.cost;
        int x = current.x;
        int y = current.y;
        int can_cast = current.can_cast;
        int temp_color = current.temp_color;
        if(x == m && y == m){
            cout << cost;
            return 0;
        }
        if(cost > distance_grid[x][y][can_cast][temp_color]){
            continue;
        }
        // Determine current color
        int current_color;
        if(temp_color == 2){
            current_color = grid[x][y];
        }
        else{
            current_color = temp_color;
        }
        for(int d=0; d<4; d++){
            int nx = x + dirs[d][0];
            int ny = y + dirs[d][1];
            if(nx <1 || nx >m || ny <1 || ny >m){
                continue;
            }
            if(grid[nx][ny] != -1){
                // Colored grid
                int neighbor_color = grid[nx][ny];
                int new_cost = cost;
                if(neighbor_color != current_color){
                    new_cost +=1;
                }
                // Determine new_can_cast
                int new_can_cast;
                if(temp_color !=2){
                    // Was on temporary grid, stepping to permanent
                    new_can_cast =1;
                }
                else{
                    new_can_cast = can_cast;
                }
                // Determine new_temp_color
                int new_temp_color =2; // permanent
                if(new_cost < distance_grid[nx][ny][new_can_cast][new_temp_color]){
                    distance_grid[nx][ny][new_can_cast][new_temp_color] = new_cost;
                    State next_state = {new_cost, nx, ny, new_can_cast, new_temp_color};
                    pq.push(next_state);
                }
            }
            else{
                // Colorless grid
                if(can_cast){
                    // Try casting spell to 0 and 1
                    for(int spell_color=0; spell_color<=1; spell_color++){
                        int additional_cost = (spell_color == current_color) ? 2 : 3;
                        int total_cost = cost + additional_cost;
                        // Set temp_color
                        int new_temp_color = spell_color;
                        int new_can_cast =0;
                        if(total_cost < distance_grid[nx][ny][new_can_cast][new_temp_color]){
                            distance_grid[nx][ny][new_can_cast][new_temp_color] = total_cost;
                            State next_state = {total_cost, nx, ny, new_can_cast, new_temp_color};
                            pq.push(next_state);
                        }
                    }
                }
            }
        }
    }
    // If destination not reached
    cout << -1;
}