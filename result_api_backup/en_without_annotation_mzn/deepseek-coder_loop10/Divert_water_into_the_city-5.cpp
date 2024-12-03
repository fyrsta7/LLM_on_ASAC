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
    vector<int> row_min(N, INT_MAX);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            row_min[i] = min(row_min[i], height[i][j]);
        }
    }

    for (int j = 0; j < M; ++j) {
        if (height[0][j] == row_min[0]) {
            build[0][j] = 1; // store
        }
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (height[i][j] == row_min[i] && (i == N-1 || height[i+1][j] > height[i][j])) {
                build[i][j] = 2; // trans
            }
        }
    }

    int desert_water = 0;
    for (int j = 0; j < M; ++j) {
        if (build[N-1][j] == 2) {
            desert_water++;
        }
    }

    int store_num = 0;
    for (int j = 0; j < M; ++j) {
        if (build[0][j] == 1) {
            store_num++;
        }
    }

    if (desert_water == M) {
        cout << "1\n" << store_num << endl;
    } else {
        cout << "0\n" << (M - desert_water) << endl;
    }

    return 0;
}
