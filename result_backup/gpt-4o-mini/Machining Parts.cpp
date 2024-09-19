#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> depths(n + 1, -1);
    queue<int> bfs_queue;
    bfs_queue.push(1);
    depths[1] = 0;

    while (!bfs_queue.empty()) {
        int current = bfs_queue.front();
        bfs_queue.pop();
        
        for (int neighbor : graph[current]) {
            if (depths[neighbor] == -1) {
                depths[neighbor] = depths[current] + 1;
                bfs_queue.push(neighbor);
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int a, L;
        cin >> a >> L;

        if (L == 1) {
            cout << (depths[a] > 0 ? "Yes" : "No") << endl;
        } else {
            cout << (depths[a] >= L ? "Yes" : "No") << endl;
        }
    }

    return 0;
}