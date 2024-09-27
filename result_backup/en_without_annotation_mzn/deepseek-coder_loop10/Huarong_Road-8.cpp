#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

int n, m, q;
vector<vector<int>> chessboard;
vector<vector<int>> location;

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int bfs(int sx, int sy, int ex, int ey, int tx, int ty) {
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<Point> q;
    q.push(Point(sx, sy));
    dist[sx][sy] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Point p = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if (isValid(nx, ny) && chessboard[nx][ny] != 0 && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[p.x][p.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }

    return dist[tx][ty] == INT_MAX ? -1 : dist[tx][ty];
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

        int steps = bfs(sx, sy, ex, ey, tx, ty);
        cout << steps << endl;
    }

    return 0;
}
