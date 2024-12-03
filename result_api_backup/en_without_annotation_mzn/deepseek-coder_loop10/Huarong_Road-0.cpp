#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

int n, m, q;
vector<vector<int>> chessboard;
vector<vector<int>> location;

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int bfs(Point start, Point end) {
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

            if (isValid(nx, ny) && chessboard[nx][ny] != 0 && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }

    return dist[end.x][end.y] == INT_MAX ? -1 : dist[end.x][end.y];
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
        Point start(location[i][0] - 1, location[i][1] - 1);
        Point end(location[i][4] - 1, location[i][5] - 1);
        int result = bfs(start, end);
        cout << result << endl;
    }

    return 0;
}
