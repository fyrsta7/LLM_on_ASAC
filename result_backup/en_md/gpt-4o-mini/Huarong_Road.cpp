#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int n, m, q;
vector<vector<int>> board;

vector<int> dx = {1, -1, 0, 0};
vector<int> dy = {0, 0, 1, -1};

bool in_bounds(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int bfs(int ex, int ey, int sx, int sy, int tx, int ty) {
    queue<tuple<int, int, int>> q;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    q.push({ex, ey, 0}); // starting from the empty space
    visited[ex][ey] = true;

    while (!q.empty()) {
        auto [x, y, steps] = q.front();
        q.pop();
        
        // Process all four directions
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (in_bounds(nx, ny) && !visited[nx][ny] && board[nx][ny] == 1) {
                visited[nx][ny] = true;
                q.push({nx, ny, steps + 1});
            }
        }
    }

    // Check how many steps it takes to reach the target piece
    if (visited[tx][ty]) {
        int steps_to_target = abs(sx - tx) + abs(sy - ty);
        return steps_to_target;
    } else {
        return -1;
    }
}

int main() {
    cin >> n >> m >> q;
    board.resize(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < q; i++) {
        int ex, ey, sx, sy, tx, ty;
        cin >> ex >> ey >> sx >> sy >> tx >> ty;
        ex--; ey--; sx--; sy--; tx--; ty--;

        int result = bfs(ex, ey, sx, sy, tx, ty);
        cout << result << endl;
    }

    return 0;
}