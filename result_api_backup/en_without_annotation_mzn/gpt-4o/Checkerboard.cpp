#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> color(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> color[i][j];

    auto is_valid = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    };

    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<int>> cost(n, vector<int>(n, INT_MAX));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    pq.emplace(0, 0, 0);
    cost[0][0] = 0;

    while (!pq.empty()) {
        auto [cur_cost, x, y] = pq.top();
        pq.pop();

        if (cur_cost > cost[x][y])
            continue;

        for (const auto& dir : directions) {
            int nx = x + dir[0], ny = y + dir[1];
            if (!is_valid(nx, ny))
                continue;

            int next_cost = cur_cost;
            if (color[x][y] != -1 && color[nx][ny] != -1 && color[x][y] != color[nx][ny])
                next_cost += 1;
            if (color[nx][ny] == -1)
                next_cost += 2;

            if (next_cost < cost[nx][ny]) {
                cost[nx][ny] = next_cost;
                pq.emplace(next_cost, nx, ny);
            }
        }
    }

    int ans = cost[n - 1][n - 1];
    if (ans == INT_MAX) ans = -1;

    cout << "ans=" << ans << endl;

    return 0;
}