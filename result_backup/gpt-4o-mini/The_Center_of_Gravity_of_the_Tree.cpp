#include <iostream>
#include <vector>
using namespace std;

class Tree {
public:
    Tree(int n) : n(n) {
        edges.resize(n + 1);
        subtree_size.resize(n + 1, 0);
        visited.resize(n + 1, false);
    }

    void add_edge(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    int calculate_center_of_gravity_sum() {
        int total_sum = 0;

        // Depth-First Search to calculate the size of each subtree
        dfs(1);

        // Now, calculate the contribution of each edge
        for (int u = 1; u <= n; u++) {
            for (int v : edges[u]) {
                if (subtree_size[v] < subtree_size[u]) {
                    total_sum += (u + v + subtree_size[v] * (n - subtree_size[v]) + (n - subtree_size[v]) * (n - subtree_size[u]));
                }
            }
        }
        return total_sum;
    }

private:
    int dfs(int node, int parent = -1) {
        visited[node] = true;
        subtree_size[node] = 1; // Count itself

        for (int neighbor : edges[node]) {
            if (!visited[neighbor]) {
                subtree_size[node] += dfs(neighbor, node);
            }
        }
        return subtree_size[node];
    }

    int n;
    vector<vector<int>> edges;
    vector<int> subtree_size;
    vector<bool> visited;
};

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        Tree tree(n);

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            tree.add_edge(u, v);
        }

        cout << tree.calculate_center_of_gravity_sum() << endl;
    }

    return 0;
}