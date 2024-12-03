#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

vector<vector<Edge>> graph;
vector<int> army, camp, time;
vector<bool> city;
int n, m;

void bfs(int start, vector<int>& dist) {
    dist.assign(n + 1, INF);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge& e : graph[u]) {
            if (dist[e.to] == INF) {
                dist[e.to] = dist[u] + e.weight;
                q.push(e.to);
            }
        }
    }
}

int main() {
    cin >> n;
    graph.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    cin >> m;
    army.resize(m);
    camp.resize(m);
    time.resize(m);
    city.assign(n + 1, false);
    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> camp[i];
        city[camp[i]] = true;
    }

    vector<int> dist_from_1(n + 1);
    bfs(1, dist_from_1);

    for (int i = 0; i < m; ++i) {
        vector<int> dist_from_army(n + 1);
        bfs(army[i], dist_from_army);
        time[i] = dist_from_army[camp[i]];
    }

    int max_time = *max_element(time.begin(), time.end());
    cout << max_time << endl;

    return 0;
}
