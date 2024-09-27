#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct State {
    int x, y, cost;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
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
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        int x = curr.x;
        int y = curr.y;
        int cost = curr.cost;

        if (x == n - 1 && y == n - 1) {
            cout << "ans=" << cost << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                int new_cost = cost;
                if (color[nx][ny] == -1) {
                    new_cost += 2;
                } else if (color[nx][ny] != color[x][y]) {
                    new_cost += 1;
                }
                if (new_cost < dist[nx][ny]) {
                    dist[nx][ny] = new_cost;
                    pq.push({nx, ny, new_cost});
                }
            }
        }
    }

    cout << "ans=" << dist[n - 1][n - 1] << endl;
    return 0;
}