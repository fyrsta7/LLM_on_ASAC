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
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        int x = curr.x, y = curr.y, cost = curr.cost;

        if (cost > dist[x][y]) continue;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

            int new_cost = cost;
            if (color[nx][ny] == -1) new_cost += 2;
            else if (color[nx][ny] != color[x][y]) new_cost += 1;

            if (new_cost < dist[nx][ny]) {
                dist[nx][ny] = new_cost;
                pq.push({nx, ny, new_cost});
            }
        }
    }

    cout << "ans=" << dist[n-1][n-1] << endl;
    return 0;
}