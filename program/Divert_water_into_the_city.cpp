#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> cities(N, vector<int>(M));
    vector<vector<int>> waterFacilities(N, vector<int>(M, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> cities[i][j];
        }
    }

    int waterPlants = 0;
    bool possible = true;

    for (int j = 0; j < M; j++) {
        if (cities[0][j] > 0) {
            waterFacilities[0][j] = 1;
            waterPlants++;
        }
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (cities[i][j] > 0) {
                bool neighborBuilt = false;
                if (j > 0 && waterFacilities[i - 1][j - 1] == 1) {
                    neighborBuilt = true;
                }
                if (j < M - 1 && waterFacilities[i - 1][j + 1] == 1) {
                    neighborBuilt = true;
                }
                if (waterFacilities[i - 1][j] == 1) {
                    neighborBuilt = true;
                }
                if (neighborBuilt) {
                    waterFacilities[i][j] = 2;
                } else {
                    possible = false;
                }
            }
        }
    }

    if (possible) {
        cout << "1" << endl;
        cout << waterPlants << endl;
    } else {
        cout << "0" << endl;
        int aridCities = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (cities[i][j] > 0 && waterFacilities[i][j] == 0) {
                    aridCities++;
                }
            }
        }
        cout << aridCities << endl;
    }

    return 0;
}