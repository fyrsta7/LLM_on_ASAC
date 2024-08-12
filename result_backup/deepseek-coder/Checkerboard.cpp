#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

const int INF = 1e9;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> color(m, vector<int>(m, -1));
    for (int i = 0; i < n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        color[x-1][y-1] = c;
    }

    vector<vector<vector<int>>> dist(m, vector<vector<int>>(m, vector<int>(2, INF)));
    dist[0][0][0] = 0;
    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;
    pq.emplace(0, 0, 0, 0);

    while (!pq.empty()) {
        auto [d, x, y, used] = pq.top();
        pq.pop();
        if (d > dist[x][y][used]) continue;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= m) continue;
            if (color[nx][ny] == -1) continue;

            if (color[nx][ny] == color[x][y]) {
                if (dist[nx][ny][used] > dist[x][y][used]) {
                    dist[nx][ny][used] = dist[x][y][used];
                    pq.emplace(dist[nx][ny][used], nx, ny, used);
                }
            } else {
                if (dist[nx][ny][used] > dist[x][y][used] + 1) {
                    dist[nx][ny][used] = dist[x][y][used] + 1;
                    pq.emplace(dist[nx][ny][used], nx, ny, used);
                }
            }
        }

        if (!used) {
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= m || ny < 0 || ny >= m) continue;
                if (color[nx][ny] != -1) continue;

                color[nx][ny] = color[x][y];
                if (dist[nx][ny][1] > dist[x][y][0] + 2) {
                    dist[nx][ny][1] = dist[x][y][0] + 2;
                    pq.emplace(dist[nx][ny][1], nx, ny, 1);
                }
                color[nx][ny] = -1;
            }
        }
    }

    int ans = min(dist[m-1][m-1][0], dist[m-1][m-1][1]);
    cout << (ans == INF ? -1 : ans) << endl;
    return 0;
}
