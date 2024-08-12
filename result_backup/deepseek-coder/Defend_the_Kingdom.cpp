#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
int cost[MAXN];
int n, m;

void bfs(int start, vector<int>& dist) {
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

ll solve(int a, int x, int b, int y) {
    vector<int> distA(n + 1, -1), distB(n + 1, -1);
    bfs(a, distA);
    bfs(b, distB);

    if (x == 0 && y == 0) {
        for (int i = 1; i <= n; ++i) {
            if (distA[i] + distB[i] == distA[b]) {
                return -1;
            }
        }
    }

    ll totalCost = 0;
    for (int i = 1; i <= n; ++i) {
        if (i == a && x == 1) {
            totalCost += cost[i];
        } else if (i == b && y == 1) {
            totalCost += cost[i];
        } else if (distA[i] == 1 && distB[i] == 1) {
            totalCost += min(cost[i], cost[a] + cost[b]);
        } else if (distA[i] == 1 && x == 0) {
            totalCost += cost[i];
        } else if (distB[i] == 1 && y == 0) {
            totalCost += cost[i];
        }
    }

    return totalCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string type;
    cin >> n >> m >> type;

    for (int i = 1; i <= n; ++i) {
        cin >> cost[i];
    }

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < m; ++i) {
        int a, x, b, y;
        cin >> a >> x >> b >> y;
        cout << solve(a, x, b, y) << '\n';
    }

    return 0;
}
