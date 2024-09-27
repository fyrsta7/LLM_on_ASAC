#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct State {
    int x, y, cost, tc;
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> color(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> color[i][j];
        }
    }

    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> tc(n, vector<int>(n, -1));
    queue<State> q;
    q.push({0, 0, 0, color[0][0] >= 0 ? color[0][0] : -1});
    dist[0][0] = 0;
    tc[0][0] = color[0][0] >= 0 ? color[0][0] : -1;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                int new_cost = curr.cost;
                int new_tc = curr.tc;

                if (color[nx][ny] == -1) {
                    new_cost += 2;
                } else if (color[nx][ny] != curr.tc) {
                    new_cost += 1;
                    new_tc = color[nx][ny];
                }

                if (dist[nx][ny] > new_cost) {
                    dist[nx][ny] = new_cost;
                    tc[nx][ny] = new_tc;
                    q.push({nx, ny, new_cost, new_tc});
                }
            }
        }
    }

    cout << "ans=" << dist[n-1][n-1] << endl;
    return 0;
}
