#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

bool isValid(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int bfs(const vector<vector<int>>& chessboard, Point start, Point end, int n, int m) {
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<Point> q;
    q.push(start);
    dist[start.x][start.y] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (isValid(nx, ny, n, m) && chessboard[nx][ny] != 0 && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }

    return dist[end.x][end.y] == INT_MAX ? -1 : dist[end.x][end.y];
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

    vector<vector<int>> location(q, vector<int>(6));
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < 6; ++j) {
            cin >> location[i][j];
        }
    }

    for (int i = 0; i < q; ++i) {
        Point start(location[i][0] - 1, location[i][1] - 1);
        Point end(location[i][2] - 1, location[i][3] - 1);
        Point target(location[i][4] - 1, location[i][5] - 1);

        int steps = bfs(chessboard, start, target, n, m);
        if (steps == -1) {
            cout << "-1\n";
        } else {
            cout << steps << "\n";
        }
    }

    return 0;
}
