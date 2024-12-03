#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

struct State {
    int x, y, steps;
};

int n, m, q;
vector<vector<int>> chessboard;
vector<tuple<int, int, int, int, int, int>> location;

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && chessboard[x][y] != 0;
}

int bfs(int sx, int sy, int ex, int ey) {
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<State> q;
    q.push({sx, sy, 0});
    dist[sx][sy] = 0;

    while (!q.empty()) {
        auto [x, y, steps] = q.front();
        q.pop();

        if (x == ex && y == ey) return steps;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = steps + 1;
                q.push({nx, ny, steps + 1});
            }
        }
    }

    return -1;
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
        int steps = bfs(sx, sy, ex, ey);
        if (steps != -1) {
            steps += bfs(ex, ey, tx, ty);
        }
        cout << (steps == -1 ? -1 : steps) << endl;
    }

    return 0;
}
