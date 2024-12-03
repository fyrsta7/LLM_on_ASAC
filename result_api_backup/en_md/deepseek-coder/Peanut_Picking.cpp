#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Plant {
    int x, y, peanuts;
};

bool compare(const Plant &a, const Plant &b) {
    return a.peanuts > b.peanuts;
}

int main() {
    int M, N, K;
    cin >> M >> N >> K;
    vector<Plant> plants;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            int peanuts;
            cin >> peanuts;
            if (peanuts > 0) {
                plants.push_back({i, j, peanuts});
            }
        }
    }
    sort(plants.begin(), plants.end(), compare);

    int time = 0, peanuts = 0;
    int currentX = 0, currentY = 0;
    for (const auto &plant : plants) {
        int travelTime = abs(plant.x - currentX) + abs(plant.y - currentY);
        if (time + travelTime + 1 + plant.x + 1 <= K) {
            time += travelTime + 1;
            peanuts += plant.peanuts;
            currentX = plant.x;
            currentY = plant.y;
        } else {
            break;
        }
    }
    cout << peanuts << endl;
    return 0;
}