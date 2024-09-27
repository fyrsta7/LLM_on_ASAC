#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> height;
vector<vector<int>> build;

bool canFlow(int x, int y) {
    if (x > 0 && height[x-1][y] > height[x][y] && build[x-1][y] != 0) return true;
    if (x < N-1 && height[x+1][y] > height[x][y] && build[x+1][y] != 0) return true;
    if (y > 0 && height[x][y-1] > height[x][y] && build[x][y-1] != 0) return true;
    if (y < M-1 && height[x][y+1] > height[x][y] && build[x][y+1] != 0) return true;
    return false;
}

int main() {
    cin >> N >> M;
    height.resize(N, vector<int>(M));
    build.resize(N, vector<int>(M, 0));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> height[i][j];
        }
    }

    for (int j = 0; j < M; ++j) {
        build[0][j] = 1; // store
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (canFlow(i, j)) {
                build[i][j] = 2; // trans
            }
        }
    }

    int desert_water = 0;
    for (int j = 0; j < M; ++j) {
        if (build[N-1][j] == 2 || build[N-1][j] == 1) {
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