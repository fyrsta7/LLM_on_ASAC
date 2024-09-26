#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

enum Water{store, trans, empty};

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> height(N, vector<int>(M));
    vector<vector<Water>> build(N, vector<Water>(M, empty));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> height[i][j];

    auto water_flow = [&](int x, int y) {
        return (x > 0 && height[x - 1][y] > height[x][y] && build[x - 1][y] != empty) ||
               (x < N - 1 && height[x + 1][y] > height[x][y] && build[x + 1][y] != empty) ||
               (y > 0 && height[x][y - 1] > height[x][y] && build[x][y - 1] != empty) ||
               (y < M - 1 && height[x][y + 1] > height[x][y] && build[x][y + 1] != empty);
    };

    for (int j = 0; j < M; ++j)
        build[0][j] = store;

    queue<tuple<int, int>> q;
    for (int j = 0; j < M; ++j)
        q.push({0, j});

    while (!q.empty()) {
        int x, y;
        tie(x, y) = q.front();
        q.pop();

        if (x == N - 1) continue;
        
        for (int i = 0; i < 4; ++i) {
            int nx = x + (i == 0 ? -1 : i == 1 ? 1 : 0);
            int ny = y + (i == 2 ? -1 : i == 3 ? 1 : 0);
            
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (height[nx][ny] > height[x][y] && build[nx][ny] == empty) {
                build[nx][ny] = trans;
                q.push({nx, ny});
            }
        }
    }

    int desert_water = 0;
    for (int j = 0; j < M; ++j)
        if (build[N - 1][j] == trans || build[N - 1][j] == store)
            desert_water++;

    int store_num = 0;
    for (int j = 0; j < M; ++j)
        if (build[0][j] == store)
            store_num++;

    if (desert_water == M) {
        cout << 1 << '\n' << store_num << '\n';
    } else {
        cout << 0 << '\n' << M - desert_water << '\n';
    }

    return 0;
}