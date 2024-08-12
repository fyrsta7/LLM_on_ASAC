#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 30;
const int MAXQ = 500;
const int INF = 1e9;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct State {
    int bx, by, px, py, steps;
};

int n, m, q;
int board[MAXN][MAXN];
int dist[MAXN][MAXN][MAXN][MAXN];

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 1;
}

void bfs(int sx, int sy) {
    queue<State> q;
    q.push({sx, sy, sx, sy, 0});
    dist[sx][sy][sx][sy] = 0;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = cur.bx + dx[i];
            int ny = cur.by + dy[i];
            if (isValid(nx, ny)) {
                if (nx == cur.px && ny == cur.py) {
                    if (dist[nx][ny][cur.bx][cur.by] > cur.steps + 1) {
                        dist[nx][ny][cur.bx][cur.by] = cur.steps + 1;
                        q.push({nx, ny, cur.bx, cur.by, cur.steps + 1});
                    }
                } else {
                    if (dist[nx][ny][cur.px][cur.py] > cur.steps + 1) {
                        dist[nx][ny][cur.px][cur.py] = cur.steps + 1;
                        q.push({nx, ny, cur.px, cur.py, cur.steps + 1});
                    }
                }
            }
        }
    }
}

int main() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < m; ++l) {
                    dist[i][j][k][l] = INF;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == 1) {
                bfs(i, j);
            }
        }
    }

    while (q--) {
        int ex, ey, sx, sy, tx, ty;
        cin >> ex >> ey >> sx >> sy >> tx >> ty;
        --ex, --ey, --sx, --sy, --tx, --ty;

        int ans = INF;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dist[ex][ey][i][j] != INF && dist[i][j][tx][ty] != INF) {
                    ans = min(ans, dist[ex][ey][i][j] + dist[i][j][tx][ty] + (i != sx || j != sy));
                }
            }
        }

        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }

    return 0;
}
