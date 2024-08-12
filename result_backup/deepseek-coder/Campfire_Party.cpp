#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 50000 + 10;
int n, adj[MAXN][2], pos[MAXN];
vector<int> cycle[MAXN];
bool visited[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> adj[i][0] >> adj[i][1];
        pos[i] = i;
    }

    for (int i = 1; i <= n; ++i) {
        if (visited[i]) continue;
        int cur = i;
        while (!visited[cur]) {
            visited[cur] = true;
            cycle[i].push_back(cur);
            cur = adj[cur][0];
        }
        for (int j : cycle[i]) {
            if (adj[j][1] != cycle[i][(find(cycle[i].begin(), cycle[i].end(), j) - cycle[i].begin() + 1) % cycle[i].size()]) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    int total_cost = 0;
    for (int i = 1; i <= n; ++i) {
        if (cycle[i].empty()) continue;
        int cycle_size = cycle[i].size();
        if (cycle_size == 1) continue;
        total_cost += cycle_size;
    }

    cout << total_cost << endl;
    return 0;
}
