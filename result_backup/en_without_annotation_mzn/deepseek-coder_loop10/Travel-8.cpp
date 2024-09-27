#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

struct Road {
    int u, v;
};

int n, m;
vector<Road> roads;

vector<int> findRoute() {
    vector<vector<int>> adj(n + 1);
    for (const auto& road : roads) {
        adj[road.u].push_back(road.v);
        adj[road.v].push_back(road.u);
    }

    vector<int> route;
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    route.push_back(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                route.push_back(v);
            }
        }
    }

    route.push_back(1);
    return route;
}

int calculateScore(const vector<int>& route) {
    unordered_map<int, int> firstOccurrence;
    for (int i = 0; i < route.size(); ++i) {
        if (firstOccurrence.find(route[i]) == firstOccurrence.end()) {
            firstOccurrence[route[i]] = i;
        }
    }

    vector<int> first(n + 1);
    for (int i = 1; i <= n; ++i) {
        first[i] = firstOccurrence[i];
    }

    sort(first.begin() + 1, first.end());

    int score = 0;
    for (int i = 1; i <= n; ++i) {
        score += pow(n, n - i) * first[i];
    }

    return score;
}

int main() {
    cin >> n >> m;
    roads.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> roads[i].u >> roads[i].v;
    }

    vector<int> route = findRoute();
    int score = calculateScore(route);

    cout << score << endl;

    return 0;
}
