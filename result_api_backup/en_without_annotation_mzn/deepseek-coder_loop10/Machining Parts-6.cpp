#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> belt(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> belt[i][0] >> belt[i][1];
    }

    vector<vector<int>> order(q, vector<int>(2));
    int L = 0;
    for (int i = 0; i < q; ++i) {
        cin >> order[i][0] >> order[i][1];
        L = max(L, order[i][1]);
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        adj[belt[i][0]].push_back(belt[i][1]);
        adj[belt[i][1]].push_back(belt[i][0]);
    }

    vector<vector<int>> produce(q, vector<int>(n + 1, 0));
    for (int i = 0; i < q; ++i) {
        int start = order[i][0];
        int time = order[i][1];
        queue<pair<int, int>> bfs;
        bfs.push({start, time});
        produce[i][start] = 1;

        while (!bfs.empty()) {
            auto [node, t] = bfs.front();
            bfs.pop();

            if (t == 0) continue;

            for (int neighbor : adj[node]) {
                if (produce[i][neighbor] == 0) {
                    produce[i][neighbor] = 1;
                    bfs.push({neighbor, t - 1});
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << (produce[i][1] > 0 ? "YES" : "NO") << endl;
    }

    return 0;
}
