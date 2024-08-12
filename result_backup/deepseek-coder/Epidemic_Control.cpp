#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 50005;
const long long INF = 1e18;

struct Edge {
    int to, w;
};

vector<Edge> graph[MAXN];
vector<int> troops, dist[MAXN];
int n, m;

void dijkstra(int start, vector<long long>& d) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    d.assign(n + 1, INF);
    d[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();
        if (dist > d[u]) continue;
        for (auto& e : graph[u]) {
            int v = e.to;
            long long w = e.w;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }
}

bool canContain(long long time) {
    vector<pair<long long, int>> troopDist;
    for (int t : troops) {
        troopDist.push_back({dist[t][1], t});
    }
    sort(troopDist.begin(), troopDist.end());

    vector<bool> covered(n + 1, false);
    vector<int> coverOrder;
    for (auto& [d, t] : troopDist) {
        if (d <= time) {
            coverOrder.push_back(t);
        } else {
            break;
        }
    }

    for (int t : coverOrder) {
        int pos = t;
        long long remainingTime = time;
        while (pos != 1 && remainingTime >= dist[pos][pos / 2]) {
            remainingTime -= dist[pos][pos / 2];
            pos = pos / 2;
        }
        covered[pos] = true;
    }

    vector<int> leafNodes;
    for (int i = 2; i <= n; ++i) {
        if (graph[i].empty()) {
            leafNodes.push_back(i);
        }
    }

    for (int leaf : leafNodes) {
        int pos = leaf;
        while (pos != 1 && !covered[pos]) {
            pos = pos / 2;
        }
        if (!covered[pos]) return false;
    }

    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    scanf("%d", &m);
    troops.resize(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &troops[i]);
    }

    for (int i = 1; i <= n; ++i) {
        dijkstra(i, dist[i]);
    }

    long long low = 0, high = INF, ans = -1;
    while (low <= high) {
        long long mid = (low + high) / 2;
        if (canContain(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
