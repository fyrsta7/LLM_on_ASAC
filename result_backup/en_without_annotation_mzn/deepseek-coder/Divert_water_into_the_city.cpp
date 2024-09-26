#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> height;
vector<vector<int>> build;

bool water_flow(int x, int y) {
    if (x > 1 && height[x-1][y] > height[x][y] && build[x-1][y] != 0) return true;
    if (x < N && height[x+1][y] > height[x][y] && build[x+1][y] != 0) return true;
    if (y > 1 && height[x][y-1] > height[x][y] && build[x][y-1] != 0) return true;
    if (y < M && height[x][y+1] > height[x][y] && build[x][y+1] != 0) return true;
    return false;
}

int main() {
    cin >> N >> M;
    height.assign(N+1, vector<int>(M+1));
    build.assign(N+1, vector<int>(M+1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> height[i][j];
        }
    }

    vector<pair<int, int>> bottom_heights;
    for (int j = 1; j <= M; ++j) {
        bottom_heights.push_back({height[N][j], j});
    }
    sort(bottom_heights.begin(), bottom_heights.end());

    int desert_water = 0;
    int store_num = 0;

    for (auto& p : bottom_heights) {
        int j = p.second;
        if (water_flow(N, j)) {
            build[N][j] = 1; // trans
            desert_water++;
        } else {
            build[N][j] = 2; // empty
        }
    }

    for (int j = 1; j <= M; ++j) {
        if (build[N][j] == 1) {
            int i = N - 1;
            while (i > 1 && water_flow(i, j)) {
                build[i][j] = 1; // trans
                --i;
            }
            if (i == 1) {
                build[1][j] = 0; // store
                store_num++;
            }
        }
    }

    int result = desert_water * M - store_num;
    cout << (desert_water == M ? "1\n" : "0\n");
    cout << (desert_water == M ? store_num : M - desert_water) << endl;

    return 0;
}