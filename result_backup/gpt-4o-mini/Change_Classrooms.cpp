#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, weight;
};

double calculateExpectedEnergy(int n, int m, vector<int>& ci, vector<int>& di, vector<double>& ki, vector<vector<Edge>>& graph) {
    vector<vector<double>> dist(v + 1, vector<double>(v + 1, INF));

    for (int i = 1; i <= v; i++) {
        dist[i][i] = 0;
    }

    for (int u = 1; u <= v; u++) {
        for (auto& edge : graph[u]) {
            dist[u][edge.to] = min(dist[u][edge.to], (double)edge.weight);
        }
    }

    for (int k = 1; k <= v; k++) {
        for (int i = 1; i <= v; i++) {
            for (int j = 1; j <= v; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    vector<double> expectedValue(n + 1, 0);
    for (int i = 1; i <= n - 1; i++) {
        expectedValue[i] = (1 - ki[i - 1]) * dist[ci[i]][ci[i + 1]] + ki[i - 1] * dist[di[i - 1]][ci[i + 1]];
    }

    sort(expectedValue.begin() + 1, expectedValue.end());
    double answer = 0;
    for (int i = 1; i <= n - m; i++) {
        answer += expectedValue[i];
    }
    return answer;
}

int main() {
    int n, m, v, e;
    cin >> n >> m >> v >> e;

    vector<int> ci(n), di(n);
    for (int i = 0; i < n; i++) {
        cin >> ci[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> di[i];
    }

    vector<double> ki(n);
    for (int i = 0; i < n; i++) {
        cin >> ki[i];
    }

    vector<vector<Edge>> graph(v + 1);
    for (int i = 0; i < e; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({ b, w });
        graph[b].push_back({ a, w });
    }

    double result = calculateExpectedEnergy(n, m, ci, di, ki, graph);
    cout << fixed << setprecision(2) << result << endl;

    return 0;
}