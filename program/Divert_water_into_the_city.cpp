#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Cell {
    int row, col, height;
    bool operator<(const Cell& other) const {
        return height > other.height;
    }
};

const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool is_valid(int row, int col, int N, int M) {
    return row >= 0 && row < N && col >= 0 && col < M;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> elevation(N, vector<int>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> elevation[i][j];

    vector<vector<bool>> visited(N, vector<bool>(M, false));
    priority_queue<Cell> pq;

    for (int j = 0; j < M; ++j) {
        pq.push({0, j, elevation[0][j]});
        visited[0][j] = true;
    }

    while (!pq.empty()) {
        Cell u = pq.top();
        pq.pop();

        for (const auto& dir : directions) {
            int newRow = u.row + dir.first;
            int newCol = u.col + dir.second;

            if (is_valid(newRow, newCol, N, M) && !visited[newRow][newCol] && elevation[newRow][newCol] <= u.height) {
                visited[newRow][newCol] = true;
                pq.push({newRow, newCol, elevation[newRow][newCol]});
            }
        }
    }

    int storage_plants_needed = 0;
    int unreachable = 0;
    for (int j = 0; j < M; ++j) {
        if (!visited[N-1][j]) {
            visited[N-1][j] = true;
            storage_plants_needed++;
            pq.push({N-1, j, elevation[N-1][j]});

            while (!pq.empty()) {
                Cell u = pq.top();
                pq.pop();

                for (const auto& dir : directions) {
                    int newRow = u.row + dir.first;
                    int newCol = u.col + dir.second;

                    if (is_valid(newRow, newCol, N, M) && !visited[newRow][newCol] && elevation[newRow][newCol] <= u.height) {
                        visited[newRow][newCol] = true;
                        pq.push({newRow, newCol, elevation[newRow][newCol]});
                    }
                }
            }
        }
    }

    for (int j = 0; j < M; ++j) {
        if (!visited[N-1][j])
            unreachable++;
    }

    if (unreachable == 0) {
        cout << 1 << endl << storage_plants_needed << endl;
    } else {
        cout << 0 << endl << unreachable << endl;
    }

    return 0;
}