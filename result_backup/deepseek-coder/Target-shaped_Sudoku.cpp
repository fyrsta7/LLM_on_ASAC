#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 9;
const int score[N][N] = {
    {10, 9, 8, 7, 6, 7, 8, 9, 10},
    {9, 10, 9, 8, 7, 8, 9, 10, 9},
    {8, 9, 10, 9, 8, 9, 10, 9, 8},
    {7, 8, 9, 10, 9, 10, 9, 8, 7},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {7, 8, 9, 10, 9, 10, 9, 8, 7},
    {8, 9, 10, 9, 8, 9, 10, 9, 8},
    {9, 10, 9, 8, 7, 8, 9, 10, 9},
    {10, 9, 8, 7, 6, 7, 8, 9, 10}
};
int grid[N][N];
bool row[N][N + 1], col[N][N + 1], box[N][N + 1];
int best_score = -1;

inline int get_box(int x, int y) {
    return (x / 3) * 3 + (y / 3);
}

void dfs(int x, int y, int cur_score) {
    if (x == N) {
        best_score = max(best_score, cur_score);
        return;
    }
    int nx = (y == N - 1) ? x + 1 : x;
    int ny = (y == N - 1) ? 0 : y + 1;
    if (grid[x][y] != 0) {
        dfs(nx, ny, cur_score);
        return;
    }
    for (int num = 1; num <= N; ++num) {
        if (!row[x][num] && !col[y][num] && !box[get_box(x, y)][num]) {
            row[x][num] = col[y][num] = box[get_box(x, y)][num] = true;
            dfs(nx, ny, cur_score + num * score[x][y]);
            row[x][num] = col[y][num] = box[get_box(x, y)][num] = false;
        }
    }
}

int main() {
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(box, 0, sizeof(box));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] != 0) {
                row[i][grid[i][j]] = true;
                col[j][grid[i][j]] = true;
                box[get_box(i, j)][grid[i][j]] = true;
            }
        }
    }
    dfs(0, 0, 0);
    cout << best_score << endl;
    return 0;
}
