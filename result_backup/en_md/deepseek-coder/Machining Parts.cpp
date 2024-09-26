#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < q; ++i) {
        int a, L;
        cin >> a >> L;

        if (L == 1) {
            if (find(adj[a].begin(), adj[a].end(), 1) != adj[a].end()) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else {
            queue<int> bfsQueue;
            vector<bool> visited(n + 1, false);
            bfsQueue.push(a);
            visited[a] = true;
            bool found = false;

            while (!bfsQueue.empty()) {
                int current = bfsQueue.front();
                bfsQueue.pop();

                for (int neighbor : adj[current]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        bfsQueue.push(neighbor);
                        if (neighbor == 1) {
                            found = true;
                            break;
                        }
                    }
                }

                if (found) break;
            }

            if (found) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}
