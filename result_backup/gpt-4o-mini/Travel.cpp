#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

vector<int> e[5001];
bool visited[5001];
vector<int> result;

void dfs(int node) {
    visited[node] = true;
    result.push_back(node);
    
    vector<int> neighbors = e[node];
    sort(neighbors.begin(), neighbors.end());
    
    for (int neighbor : neighbors) {
        if (!visited[neighbor]) {
            dfs(neighbor);
            result.push_back(node); // return to the previous city
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    result.reserve(2 * n); // reserve space for the final result
    dfs(1); // start DFS from the first city

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    
    return 0;
}