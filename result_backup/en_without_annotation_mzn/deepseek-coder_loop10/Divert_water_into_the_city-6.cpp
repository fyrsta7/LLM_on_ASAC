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

    vector<pair<int, int>> heights;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            heights.emplace_back(height[i][j], i * (M+1) + j);
        }
    }
    sort(heights.rbegin(), heights.rend());

    int desert_water = 0;
    int store_num = 0;

    for (auto& h : heights) {
        int x = h.second / (M+1);
        int y = h.second % (M+1);

        if (x == 1) {
            build[x][y] = 1;
            store_num++;
        } else if (water_flow(x, y)) {
            build[x][y] = 2;
        } else {
            build[x][y] = 0;
        }

        if (x == N && (build[x][y] == 1 || build[x][y] == 2)) {
            desert_water++;
        }
    }

    if (desert_water == M) {
        cout << "1\n" << store_num << endl;
    } else {
        cout << "0\n" << (M - desert_water) << endl;
    }

    return 0;
}