#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Edge {
    int u, v, length;
};

int n, m;
vector<Edge> edges;

bool canDistribute(int minLength) {
    vector<bool> visited(n + 1, false);
    int count = 0;
    
    for (const auto& edge : edges) {
        if (edge.length >= minLength) {
            if (!visited[edge.u] || !visited[edge.v]) {
                visited[edge.u] = visited[edge.v] = true;
                count++;
            }
            if (count >= m) return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    edges.resize(n - 1);
    
    for (int i = 0; i < n - 1; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].length;
    }

    int left = 1, right = accumulate(edges.begin(), edges.end(), 0, [](int sum, const Edge& e) { return sum + e.length; });
    int result = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (canDistribute(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << result << endl;
    return 0;
}