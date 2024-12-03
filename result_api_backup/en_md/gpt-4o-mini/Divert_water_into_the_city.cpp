#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> heights(N, vector<int>(M));
    vector<vector<bool>> hasWaterFacility(N, vector<bool>(M, false));
    queue<pair<int, int>> q;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> heights[i][j];
        }
    }

    // Build water storage plants in row 0
    for (int j = 0; j < M; j++) {
        hasWaterFacility[0][j] = true;
        q.push({0, j});
    }

    // Directions: up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // BFS to mark cities that can receive water
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && !hasWaterFacility[nx][ny] && heights[nx][ny] < heights[x][y]) {
                hasWaterFacility[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    
    // Count cities in arid areas where water facilities cannot be built
    int unwateredCount = 0;
    for (int j = 0; j < M; j++) {
        if (!hasWaterFacility[N-1][j]) { // Check last row, desert area
            unwateredCount++;
        }
    }

    if (unwateredCount == 0) {
        cout << 1 << endl; // Requirements can be met
        cout << 1 << endl; // At least 1 storage plant in the first row
    } else {
        cout << 0 << endl; // Requirements cannot be met
        cout << unwateredCount << endl; // Number of unwatered cities
    }
    
    return 0;
}