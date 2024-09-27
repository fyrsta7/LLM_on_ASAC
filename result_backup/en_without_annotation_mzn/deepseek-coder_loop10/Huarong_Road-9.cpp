#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, m, q;
vector<vector<int>> chessboard;
vector<tuple<int, int, int, int, int, int>> location;

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int bfs(int sx, int sy, int ex, int ey, int tx, int ty) {
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    dist[sx][sy] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) && dist[nx][ny] == -1 && chessboard[nx][ny] != 0) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return dist[ex][ey] == -1 ? -1 : dist[ex][ey] + dist[tx][ty];
}

int main() {
    cin >> n >> m >> q;
    chessboard.resize(n, vector<int>(m));
    location.resize(q);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> chessboard[i][j];
        }
    }

    for (int i = 0; i < q; ++i) {
        int sx, sy, ex, ey, tx, ty;
        cin >> sx >> sy >> ex >> ey >> tx >> ty;
        location[i] = {sx - 1, sy - 1, ex - 1, ey - 1, tx - 1, ty - 1};
    }

    for (int i = 0; i < q; ++i) {
        auto [sx, sy, ex, ey, tx, ty] = location[i];
        int steps = bfs(sx, sy, ex, ey, tx, ty);
        cout << (steps == -1 ? -1 : steps) << endl;
    }

    return 0;
}
