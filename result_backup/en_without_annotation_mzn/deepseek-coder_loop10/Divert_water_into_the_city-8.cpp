#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> height(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> height[i][j];
        }
    }

    vector<vector<int>> build(N, vector<int>(M, 0));
    vector<int> store_positions;

    // Initialize the first row
    for (int j = 0; j < M; ++j) {
        if (height[0][j] > height[1][j]) {
            build[0][j] = 1; // store
            store_positions.push_back(j);
        } else {
            build[0][j] = 2; // trans
        }
    }

    // Propagate water flow
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (height[i][j] < height[i-1][j] && build[i-1][j] != 0) {
                build[i][j] = 2; // trans
            } else {
                build[i][j] = 0; // empty
            }
        }
    }

    int desert_water = 0;
    for (int j = 0; j < M; ++j) {
        if (build[N-1][j] == 2) {
            ++desert_water;
        }
    }

    int store_num = store_positions.size();
    int result = desert_water * M - store_num;

    if (desert_water == M) {
        cout << "1\n" << store_num << endl;
    } else {
        cout << "0\n" << (M - desert_water) << endl;
    }

    return 0;
}