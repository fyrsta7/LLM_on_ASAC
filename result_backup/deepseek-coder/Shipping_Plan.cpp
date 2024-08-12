#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

vector<pair<int, int>> adj[MAXN];
int dist[MAXN], parent[MAXN];
bool inQueue[MAXN];

void spfa(int start) {
    queue<int> q;
    fill(dist, dist + MAXN, INF);
    fill(inQueue, inQueue + MAXN, false);
    dist[start] = 0;
    q.push(start);
    inQueue[start] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;
        for (auto &edge : adj[u]) {
            int v = edge.first, w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        adj[a].emplace_back(b, t);
        adj[b].emplace_back(a, t);
    }

    vector<pair<int, int>> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
    }

    int minTime = INF;
    for (int i = 1; i <= n; ++i) {
        spfa(i);
        int maxDist = 0;
        for (auto &plan : plans) {
            maxDist = max(maxDist, dist[plan.first] + dist[plan.second]);
        }
        minTime = min(minTime, maxDist);
    }

    cout << minTime << endl;
    return 0;
}
