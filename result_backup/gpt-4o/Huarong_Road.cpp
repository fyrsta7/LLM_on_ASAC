#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

const int MAXN = 31;
const int INF = 1e9;
int n, m, q;
int board[MAXN][MAXN];
int dist[MAXN][MAXN][MAXN][MAXN];

struct State {
    int x_blank, y_blank, x_piece, y_piece, moves;
};

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 1;
}

int bfs(int ex, int ey, int sx, int sy, int tx, int ty) {
    if (sx == tx && sy == ty) return 0; // Already at the goal

    memset(dist, -1, sizeof(dist));
    queue<State> q;
    q.push({ex, ey, sx, sy, 0});
    dist[ex][ey][sx][sy] = 0;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.x_piece == tx && cur.y_piece == ty) 
            return cur.moves;

        for (int i = 0; i < 4; ++i) {
            int new_x_blank = cur.x_blank + dx[i];
            int new_y_blank = cur.y_blank + dy[i];

            if (!isValid(new_x_blank, new_y_blank)) continue;

            int new_x_piece = cur.x_piece;
            int new_y_piece = cur.y_piece;

            if (new_x_blank == cur.x_piece && new_y_blank == cur.y_piece) {
                new_x_piece = cur.x_blank;
                new_y_piece = cur.y_blank;
            }

            if (dist[new_x_blank][new_y_blank][new_x_piece][new_y_piece] == -1) {
                dist[new_x_blank][new_y_blank][new_x_piece][new_y_piece] = cur.moves + 1;
                q.push({new_x_blank, new_y_blank, new_x_piece, new_y_piece, cur.moves + 1});
            }
        }
    }

    return -1; // Not possible to reach the target
}

int main() {
    cin >> n >> m >> q;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> board[i][j];

    while (q--) {
        int ex, ey, sx, sy, tx, ty;
        cin >> ex >> ey >> sx >> sy >> tx >> ty;
        ex--, ey--, sx--, sy--, tx--, ty--;
        cout << bfs(ex, ey, sx, sy, tx, ty) << "\n";
    }

    return 0;
}