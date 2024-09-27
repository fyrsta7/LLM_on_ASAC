#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct State {
    int x, y, steps;
};

bool isValid(int x, int y, int n, int m, const vector<vector<int>>& chessboard) {
    return x >= 0 && x < n && y >= 0 && y < m && chessboard[x][y] != 0;
}

int bfs(int n, int m, const vector<vector<int>>& chessboard, int sx, int sy, int ex, int ey) {
    vector<vector<int>> dist(n, vector<int>(m, INF));
    queue<State> q;
    q.push({sx, sy, 0});
    dist[sx][sy] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [x, y, steps] = q.front();
        q.pop();

        if (x == ex && y == ey) return steps;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, n, m, chessboard) && dist[nx][ny] == INF) {
                dist[nx][ny] = steps + 1;
                q.push({nx, ny, steps + 1});
            }
        }
    }

    return -1;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> chessboard(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> chessboard[i][j];
        }
    }

    vector<tuple<int, int, int, int, int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int sx, sy, ex, ey, tx, ty;
        cin >> sx >> sy >> ex >> ey >> tx >> ty;
        queries[i] = {sx - 1, sy - 1, ex - 1, ey - 1, tx - 1, ty - 1};
    }

    for (const auto& [sx, sy, ex, ey, tx, ty] : queries) {
        int steps = bfs(n, m, chessboard, sx, sy, ex, ey);
        if (steps == -1) {
            cout << "-1\n";
        } else {
            int final_steps = bfs(n, m, chessboard, ex, ey, tx, ty);
            if (final_steps == -1) {
                cout << "-1\n";
            } else {
                cout << steps + final_steps << "\n";
            }
        }
    }

    return 0;
}
