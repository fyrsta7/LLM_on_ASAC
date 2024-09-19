#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

struct Edge {
    int to, weight;
};

vector<vector<Edge>> adjList;
vector<vector<double>> minPathEnergy;
vector<int> c, d;
vector<double> k;

void dijkstra(int start, int classroomCount) {
    vector<double> dist(classroomCount + 1, numeric_limits<double>::infinity());
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    dist[start] = 0.0;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [currentCost, u] = pq.top();
        pq.pop();

        if (currentCost > dist[u]) continue;

        for (const auto& edge : adjList[u]) {
            int v = edge.to;
            double weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= classroomCount; ++i) {
        minPathEnergy[start][i] = dist[i];
    }
}

int main() {
    int n, m, v, e;
    cin >> n >> m >> v >> e;

    c.resize(n);
    d.resize(n);
    k.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> k[i];
    }

    adjList.resize(v + 1);
    minPathEnergy.assign(v + 1, vector<double>(v + 1, numeric_limits<double>::infinity()));

    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        adjList[a].push_back({b, w});
        adjList[b].push_back({a, w});
    }

    for (int i = 1; i <= v; ++i) {
        dijkstra(i, v);
    }

    vector<double> dp((1 << n), numeric_limits<double>::infinity());
    dp[0] = 0.0;

    for (int mask = 0; mask < (1 << n); ++mask) {
        int curClassroom = c[0];
        double curEnergy = 0.0;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                curClassroom = d[i];
            } else {
                curClassroom = c[i];
            }
            if (i > 0) {
                int prevClassroom = (mask & (1 << (i - 1))) ? d[i - 1] : c[i - 1];
                curEnergy += dp[mask ^ (1 << i)];
            }
        }

        dp[mask] = (dp[mask] * (1 - k[i])) + (curEnergy * k[i]);

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                dp[mask] = min(dp[mask], dp[mask ^ (1 << i)] + minPathEnergy[c[i]][d[i]] * k[i]);
            }
        }
    }

    double result = numeric_limits<double>::infinity();
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) <= m) {
            result = min(result, dp[mask]);
        }
    }

    cout.precision(2);
    cout << fixed << result << endl;
    return 0;
}