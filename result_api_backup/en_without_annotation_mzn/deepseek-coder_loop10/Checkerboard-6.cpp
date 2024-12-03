#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct State {
    int x, y, cost, tc;
    State(int x, int y, int cost, int tc) : x(x), y(y), cost(cost), tc(tc) {}
};

struct CompareState {
    bool operator()(const State& a, const State& b) {
        return a.cost > b.cost;
    }
};

int dijkstra(int n, const vector<vector<int>>& color) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    priority_queue<State, vector<State>, CompareState> pq;

    pq.emplace(1, 1, 0, color[1][1] >= 0 ? color[1][1] : 0);
    dist[1][1] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        if (curr.x == n && curr.y == n) return curr.cost;

        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;

            int new_cost = curr.cost;
            int new_tc = curr.tc;

            if (color[nx][ny] == -1) {
                new_cost += 2;
            } else if (color[nx][ny] != curr.tc) {
                new_cost += 1;
                new_tc = color[nx][ny];
            }

            if (new_cost < dist[nx][ny]) {
                dist[nx][ny] = new_cost;
                pq.emplace(nx, ny, new_cost, new_tc);
            }
        }
    }

    return dist[n][n];
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> color(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> color[i][j];
        }
    }

    int ans = dijkstra(n, color);
    cout << "ans=" << ans << endl;

    return 0;
}
