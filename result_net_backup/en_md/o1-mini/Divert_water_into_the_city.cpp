#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

struct City {
    int x, y;
};

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> height(N, vector<int>(M));
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<bool>> hasFacility(N, vector<bool>(M, false));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> height[i][j];

    // Directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    queue<City> q;

    // Step 1: Build water storage plants in row 0 (cities adjacent to the lake)
    for (int j = 0; j < M; ++j) {
        visited[0][j] = true;
        hasFacility[0][j] = true;
        q.push({0, j});
    }

    // Step 2: BFS to simulate water transmission stations
    while (!q.empty()) {
        City current = q.front();
        q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            int nx = current.x + dx[dir], ny = current.y + dy[dir];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && height[nx][ny] < height[current.x][current.y]) {
                visited[nx][ny] = true;
                hasFacility[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    // Step 3: Check if all cities in the last row (arid areas) have facilities
    int unservedCities = 0;
    for (int j = 0; j < M; ++j) {
        if (!hasFacility[N-1][j]) {
            unservedCities++;
        }
    }

    if (unservedCities == 0) {
        // Step 4: Calculate the minimum number of water storage plants required
        int storagePlants = 0;
        for (int j = 0; j < M; ++j) {
            if (hasFacility[0][j]) continue;
            bool canServe = false;
            for (int i = 0; i < N; ++i) {
                for (int k = 0; k < M; ++k) {
                    if (hasFacility[i][k] && abs(height[i][k] - height[0][j]) > 0) {
                        canServe = true;
                        break;
                    }
                }
            }
            if (canServe) storagePlants++;
        }
        cout << "1\n" << storagePlants << endl;
    } else {
        cout << "0\n" << unservedCities << endl;
    }

    return 0;
}