#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int to, weight;
};

vector<vector<Edge>> tree;
vector<int> dist;

// Perform BFS and return the farthest node and its distance
pair<int, int> bfs(int start) {
    int n = tree.size();
    dist.assign(n, INT_MAX);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    int farthest_node = start;
    int max_dist = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &e : tree[u]) {
            int v = e.to;
            if (dist[v] > dist[u] + e.weight) {
                dist[v] = dist[u] + e.weight;
                q.push(v);
                if (dist[v] > max_dist) {
                    max_dist = dist[v];
                    farthest_node = v;
                }
            }
        }
    }
    return {farthest_node, max_dist};
}

// Find the diameter of the tree
pair<int, int> find_diameter() {
    auto t1 = bfs(0);
    auto t2 = bfs(t1.first);
    return {t1.first, t2.first};
}

// DFS to collect distances from the current path to all nodes in the subtree
void dfs(int u, int parent, int d, vector<int> &dist_to_path) {
    dist_to_path[u] = d;
    for (auto &e : tree[u]) {
        int v = e.to;
        if (v != parent) {
            dfs(v, u, d + e.weight, dist_to_path);
        }
    }
}

int main() {
    int n, s;
    cin >> n >> s;

    tree.resize(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }

    auto diameter_nodes = find_diameter();
    int u = diameter_nodes.first;
    int v = diameter_nodes.second;

    // Find the path from u to v
    vector<int> path;
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    parent[u] = u;
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while (!q.empty() && !visited[v]) {
        int cur = q.front();
        q.pop();
        for (auto &e : tree[cur]) {
            int next = e.to;
            if (!visited[next]) {
                parent[next] = cur;
                visited[next] = true;
                q.push(next);
            }
        }
    }

    for (int node = v; node != u; node = parent[node]) {
        path.push_back(node);
    }
    path.push_back(u);

    reverse(path.begin(), path.end());

    vector<int> prefix_sum(path.size());
    vector<int> prefix_max(path.size());
    prefix_sum[0] = 0;
    for (int i = 1; i < path.size(); ++i) {
        for (auto &e : tree[path[i-1]]) {
            if (e.to == path[i]) {
                prefix_sum[i] = prefix_sum[i-1] + e.weight;
                break;
            }
        }
    }

    prefix_max = prefix_sum;
    for (int i = 1; i < path.size(); ++i) {
        prefix_max[i] = max(prefix_max[i-1], prefix_sum[i]);
    }

    vector<int> suffix_sum(path.size());
    vector<int> suffix_max(path.size());
    suffix_sum.back() = 0;
    for (int i = path.size() - 2; i >= 0; --i) {
        for (auto &e : tree[path[i]]) {
            if (e.to == path[i+1]) {
                suffix_sum[i] = suffix_sum[i+1] + e.weight;
                break;
            }
        }
    }

    suffix_max = suffix_sum;
    for (int i = path.size() - 2; i >= 0; --i) {
        suffix_max[i] = max(suffix_max[i+1], suffix_sum[i]);
    }

    int min_eccentricity = INT_MAX;
    for (int i = 0; i < path.size(); ++i) {
        int left = i;
        int right = i;
        while (right < path.size() && prefix_sum[right] - prefix_sum[left] <= s) {
            ++right;
        }
        if (right - 1 >= i) {
            int ecc = max(prefix_max[left], suffix_max[right-1]);
            min_eccentricity = min(min_eccentricity, ecc);
        }
    }

    cout << min_eccentricity << "\n";

    return 0;
}