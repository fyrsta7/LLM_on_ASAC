#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

const int INF = 1e9;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

struct Cell {
    int x, y, cost;
};

int main() {
    int m, n;
    cin >> m >> n;
    
    vector<vector<int>> board(m + 1, vector<int>(m + 1, -1));
    
    for (int i = 0; i < n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        board[x][y] = c;
    }
    
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    vector<vector<vector<int>>> dist(m + 1, vector<vector<int>>(m + 1, vector<int>(2, INF)));
    
    dist[1][1][0] = 0;
    pq.push({1, 1, 0});
    
    while (!pq.empty()) {
        auto [x, y, currentCost] = pq.top();
        pq.pop();
        
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 1 && nx <= m && ny >= 1 && ny <= m) {
                int nextCost = currentCost;
                if (board[nx][ny] == -1) continue; // skip colorless
                
                if (board[x][y] == board[nx][ny]) {
                    // same color, no cost
                } else {
                    nextCost += 1; // different color, cost 1
                }
                
                if (nextCost < dist[nx][ny][0]) {
                    dist[nx][ny][0] = nextCost;
                    pq.push({nx, ny, nextCost});
                }
            }
        }
        
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 1 && nx <= m && ny >= 1 && ny <= m) {
                if (board[nx][ny] == -1) {
                    // colorless, we can cast a spell
                    int spellCost = currentCost + 2; // cost of spell
                    if (board[x][y] != -1) {
                        // we can change color to board[x][y]
                        if (spellCost < dist[nx][ny][1]) {
                            dist[nx][ny][1] = spellCost;
                            pq.push({nx, ny, spellCost});
                        }
                    }
                }
            }
        }
    }
    
    int result = min(dist[m][m][0], dist[m][m][1]);
    cout << (result == INF ? -1 : result) << endl;
    return 0;
}