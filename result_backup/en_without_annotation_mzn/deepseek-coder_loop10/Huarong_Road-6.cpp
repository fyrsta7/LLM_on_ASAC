#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int INF = 1e9;

int n, m, q;
vector<vector<int>> chessboard;
vector<vector<int>> location;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int bfs(int sx, int sy, int ex, int ey) {
    vector<vector<int>> dist(n, vector<int>(m, INF));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    dist[sx][sy] = 0;

    while (!q.empty()) {
        int x, y;
        tie(x, y) = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) && chessboard[nx][ny] != 0 && dist[nx][ny] == INF) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return dist[ex][ey] == INF ? -1 : dist[ex][ey];
}

int main() {
    cin >> n >> m >> q;
    chessboard.resize(n, vector<int>(m));
    location.resize(q, vector<int>(6));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> chessboard[i][j];
        }
    }

    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < 6; ++j) {
            cin >> location[i][j];
        }
    }

    for (int i = 0; i < q; ++i) {
        int sx = location[i][0] - 1;
        int sy = location[i][1] - 1;
        int ex = location[i][2] - 1;
        int ey = location[i][3] - 1;
        int tx = location[i][4] - 1;
        int ty = location[i][5] - 1;

        int steps = bfs(sx, sy, ex, ey);
        if (steps != -1) {
            steps += bfs(ex, ey, tx, ty);
        }

        cout << (steps == -1 ? -1 : steps) << endl;
    }

    return 0;
}