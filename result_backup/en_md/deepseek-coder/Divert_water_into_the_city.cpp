#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1005;
int grid[MAXN][MAXN];
bool visited[MAXN][MAXN];
int N, M;

struct Node {
    int x, y;
    Node(int _x, int _y) : x(_x), y(_y) {}
};

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

void bfs(int x, int y) {
    queue<Node> q;
    q.push(Node(x, y));
    visited[x][y] = true;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Node curr = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny] && grid[nx][ny] <= grid[curr.x][curr.y]) {
                visited[nx][ny] = true;
                q.push(Node(nx, ny));
            }
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
        }
    }

    int storagePlants = 0;
    for (int j = 0; j < M; ++j) {
        if (!visited[0][j]) {
            bfs(0, j);
            storagePlants++;
        }
    }

    int unreachableCities = 0;
    for (int j = 0; j < M; ++j) {
        if (!visited[N-1][j]) {
            unreachableCities++;
        }
    }

    if (unreachableCities == 0) {
        cout << 1 << endl;
        cout << storagePlants << endl;
    } else {
        cout << 0 << endl;
        cout << unreachableCities << endl;
    }

    return 0;
}
