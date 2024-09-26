#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 20000 + 5;
const int MAXM = 100000 + 5;

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

vector<Edge> graph[MAXN];
int dist[MAXN];
bool inQueue[MAXN];

void spfa(int start, int n) {
    fill(dist, dist + n + 1, INT_MAX);
    fill(inQueue, inQueue + n + 1, false);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    inQueue[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (const Edge &e : graph[u]) {
            int v = e.to;
            int w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
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

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }

    spfa(1, n);

    int maxDist = 0;
    for (int i = 1; i <= n; ++i) {
        maxDist = max(maxDist, dist[i]);
    }

    cout << maxDist << endl;

    return 0;
}
