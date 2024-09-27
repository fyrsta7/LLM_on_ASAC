#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;

struct Node {
    int x, y, cost;
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int dijkstra(int n, const vector<vector<int>>& color) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({1, 1, 0});
    dist[1][1] = 0;

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        int x = curr.x, y = curr.y, cost = curr.cost;

        if (x == n && y == n) return cost;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (abs(dx) + abs(dy) == 1) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                        int new_cost = cost;
                        if (color[nx][ny] == -1) new_cost += 2;
                        else if (color[nx][ny] != color[x][y]) new_cost += 1;

                        if (new_cost < dist[nx][ny]) {
                            dist[nx][ny] = new_cost;
                            pq.push({nx, ny, new_cost});
                        }
                    }
                }
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