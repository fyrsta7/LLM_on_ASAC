#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

struct State {
    int x, y, steps;
    vector<vector<int>> board;
};

int n, m, q;
vector<vector<int>> chessboard;
vector<tuple<int, int, int, int, int, int>> location;

bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int bfs(const State &start, int lx, int ly) {
    queue<State> que;
    que.push(start);

    while (!que.empty()) {
        State cur = que.front();
        que.pop();

        if (cur.board[lx][ly] == 2) {
            return cur.steps;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (is_valid(nx, ny) && cur.board[nx][ny] != 0 && cur.board[nx][ny] != -1) {
                vector<vector<int>> new_board = cur.board;
                swap(new_board[cur.x][cur.y], new_board[nx][ny]);

                que.push({nx, ny, cur.steps + 1, new_board});
            }
        }
    }

    return -1;
}

int main() {
    cin >> n >> m >> q;
    chessboard = vector<vector<int>>(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> chessboard[i][j];

    location = vector<tuple<int, int, int, int, int, int>>(q);

    for (int i = 0; i < q; ++i) {
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        location[i] = make_tuple(x1 - 1, y1 - 1, x2 - 1, y2 - 1, x3 - 1, y3 - 1);
    }

    for (const auto& loc : location) {
        int sx, sy, ex, ey, gx, gy;
        tie(sx, sy, ex, ey, gx, gy) = loc;

        vector<vector<int>> start_board = chessboard;
        start_board[sx][sy] = -1;
        start_board[ex][ey] = 2;

        State start = {sx, sy, 0, start_board};
        int result = bfs(start, gx, gy);

        cout << result << endl;
    }

    return 0;
}