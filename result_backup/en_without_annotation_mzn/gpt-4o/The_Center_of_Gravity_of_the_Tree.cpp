#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int n;
vector<pair<int, int>> edges;
vector<set<int>> subtree(2 * 1000); // An upper bound on the number of nodes and edges.

bool isConnected(int a, int b, const set<int>& e) {
    vector<bool> visited(n + 1, false);
    vector<int> stack = { a };
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        if (visited[node]) continue;
        visited[node] = true;
        if (node == b) return true;
        for (auto& edge : edges) {
            if (e.find(edge.first) != e.end()) continue;
            if (edge.first == node && !visited[edge.second])
                stack.push_back(edge.second);
            if (edge.second == node && !visited[edge.first])
                stack.push_back(edge.first);
        }
    }
    return false;
}

int main() {
    cin >> n;
    edges.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (find_if(edges.begin(), edges.end(), [&](pair<int, int> edge) { return edge.first == j && (subtree[i * 2 + 1].count(edge.second) > 0 || subtree[i * 2 + 2].count(edge.second) > 0); }) != edges.end()) {
                subtree[i * 2].insert(j);
            } else {
                subtree[i * 2 + 1].insert(j);
            }
        }
    }

    vector<int> center(n - 1);

    for (int i = 0; i < n - 1; ++i) {
        center[i] = *subtree[i * 2].begin();
    }

    for (int i = 0; i < n - 1; ++i) {
        cout << center[i] << " ";
    }
    cout << endl;

    return 0;
}