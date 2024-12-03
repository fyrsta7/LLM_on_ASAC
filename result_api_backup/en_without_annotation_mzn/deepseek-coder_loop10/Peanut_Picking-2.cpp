#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;

struct State {
    int x, y, k, num;
    unordered_set<int> picked;
    vector<int> actions;
};

int M, N, K;
vector<vector<int>> peanuts;
unordered_set<int> peanut_set;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

int main() {
    cin >> M >> N >> K;
    peanuts.resize(M, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> peanuts[i][j];
            if (peanuts[i][j] > 0) peanut_set.insert(peanuts[i][j]);
        }
    }

    queue<State> q;
    q.push({0, 0, K, 0, {}, {}});

    int maxNum = 0;
    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.k == 0) {
            if (curr.x == 0 && curr.y == 0) {
                maxNum = max(maxNum, curr.num);
            }
            continue;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = curr.x + dx[d];
            int ny = curr.y + dy[d];
            if (isValid(nx, ny)) {
                State next = curr;
                next.x = nx;
                next.y = ny;
                next.k--;
                if (peanuts[nx][ny] > 0 && curr.picked.find(peanuts[nx][ny]) == curr.picked.end()) {
                    next.num += peanuts[nx][ny];
                    next.picked.insert(peanuts[nx][ny]);
                    next.actions.push_back(peanuts[nx][ny]);
                }
                q.push(next);
            }
        }
    }

    cout << maxNum << endl;
    return 0;
}
