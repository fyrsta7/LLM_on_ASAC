#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

const int DIRS = 4;
const int dx[DIRS] = {1, -1, 0, 0};
const int dy[DIRS] = {0, 0, 1, -1};

struct Cell {
    int x, y, cost;
    Cell(int x, int y, int cost) : x(x), y(y), cost(cost) {}
    bool operator>(const Cell& other) const {
        return cost > other.cost;
    }
};

int minGoldCoins(int m, int n, vector<vector<int>>& board) {
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    vector<vector<int>> cost(m, vector<int>(m, INT_MAX));
    pq.emplace(0, 0, 0);
    cost[0][0] = 0;

    while (!pq.empty()) {
        auto [cx, cy, curr_cost] = pq.top();
        pq.pop();

        if (curr_cost > cost[cx][cy]) continue;
        if (cx == m-1 && cy == m-1) return curr_cost;

        for (int d = 0; d < DIRS; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (nx >= 0 && nx < m && ny >= 0 && ny < m) {
                int new_cost = curr_cost;
                if (board[nx][ny] == -1) {
                    new_cost += 2;
                    for (int k = 0; k < DIRS; ++k) {
                        int nnx = nx + dx[k];
                        int nny = ny + dy[k];
                        if (nnx >= 0 && nnx < m && nny >= 0 && nny < m && board[nnx][nny] != -1) {
                            int temp_cost = new_cost;
                            if (board[cx][cy] != board[nnx][nny]) temp_cost += 1;
                            if (temp_cost < cost[nnx][nny]) {
                                cost[nnx][nny] = temp_cost;
                                pq.emplace(nnx, nny, temp_cost);
                            }
                        }
                    }
                } else {
                    if (board[cx][cy] != board[nx][ny]) new_cost += 1;
                    if (new_cost < cost[nx][ny]) {
                        cost[nx][ny] = new_cost;
                        pq.emplace(nx, ny, new_cost);
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> board(m, vector<int>(m, -1)); // -1 for colorless
    for (int i = 0; i < n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        board[--x][--y] = c; // switch to 0-based indexing
    }

    int result = minGoldCoins(m, n, board);
    cout << result << endl;

    return 0;
}