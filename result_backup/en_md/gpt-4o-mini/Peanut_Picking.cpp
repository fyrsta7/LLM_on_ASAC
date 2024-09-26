#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct PeanutPlant {
    int row, col, peanuts;
};

int main() {
    int M, N, K;
    cin >> M >> N >> K;

    vector<vector<int>> field(M, vector<int>(N, 0));
    vector<PeanutPlant> plants;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> field[i][j];
            if (field[i][j] > 0) {
                plants.push_back({i, j, field[i][j]});
            }
        }
    }

    // Sort plants based on the peanut count in descending order
    sort(plants.begin(), plants.end(), [](PeanutPlant a, PeanutPlant b) {
        return a.peanuts > b.peanuts;
    });

    int maxPeanuts = 0;

    for (int mask = 0; mask < (1 << plants.size()); mask++) {
        int timeSpent = 0;
        int peanutsCollected = 0;
        vector<bool> visited(plants.size(), false);

        for (int i = 0; i < plants.size(); i++) {
            if (mask & (1 << i)) {
                if (visited[i]) continue;

                int row = plants[i].row;
                int col = plants[i].col;
                int peanuts = plants[i].peanuts;

                // Time to jump to the plant
                timeSpent += (row + 1) + 1; // Row to ground + pick
                if (timeSpent > K) break;

                peanutsCollected += peanuts;
                visited[i] = true;

                // Time to jump back
                timeSpent += row + 1; // Jump back to ground
                if (timeSpent > K) break;
            }
        }

        maxPeanuts = max(maxPeanuts, peanutsCollected);
    }

    cout << maxPeanuts << endl;
    return 0;
}