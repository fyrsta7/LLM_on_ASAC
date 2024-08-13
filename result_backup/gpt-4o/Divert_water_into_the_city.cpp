#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int N, M;

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

void bfs(vector<vector<int>>& elevation, vector<vector<bool>>& canBeIrrigated, queue<pair<int, int>>& q) {
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + directions[i][0], ny = y + directions[i][1];
            if (isValid(nx, ny) && elevation[nx][ny] < elevation[x][y] && !canBeIrrigated[nx][ny]) {
                canBeIrrigated[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    cin >> N >> M;
    vector<vector<int>> elevation(N, vector<int>(M));
    vector<vector<bool>> canBeIrrigated(N, vector<bool>(M, false));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> elevation[i][j];
        }
    }

    queue<pair<int, int>> q;
    int minWaterStoragePlants = 0;

    for (int j = 0; j < M; ++j) {
        if (!canBeIrrigated[0][j]) {
            ++minWaterStoragePlants;
            q.push({0, j});
            canBeIrrigated[0][j] = true;
        }
        bfs(elevation, canBeIrrigated, q);
    }

    int aridCities = 0;
    for (int j = 0; j < M; ++j) {
        if (!canBeIrrigated[N-1][j]) {
            ++aridCities;
        }
    }

    if (aridCities > 0) {
        cout << 0 << endl << aridCities << endl;
    } else {
        cout << 1 << endl << minWaterStoragePlants << endl;
    }

    return 0;
}