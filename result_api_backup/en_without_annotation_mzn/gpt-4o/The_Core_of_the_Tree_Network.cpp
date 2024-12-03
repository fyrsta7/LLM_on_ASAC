#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int u, v, weight;
};

int n, s;
vector<Edge> edges;

int find_route(int a, int b, vector<int>& path) {
    vector<int> dist(n, INT_MAX), pred(n, -1);
    dist[a] = 0;
    for(int i = 0; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
                pred[edge.v] = edge.u;
            }
            if (dist[edge.v] + edge.weight < dist[edge.u]) {
                dist[edge.u] = dist[edge.v] + edge.weight;
                pred[edge.u] = edge.v;
            }
        }
    }

    if (dist[b] == INT_MAX) return INT_MAX;
    
    for (int u = b; u != -1; u = pred[u])
        path.push_back(u);
    
    reverse(path.begin(), path.end());
    return dist[b];
}

int get_distance(const vector<int>& roads) {
    int total_weight = 0;
    for (size_t i = 0; i < roads.size() - 1; ++i) {
        for (const auto& edge : edges) {
            if ((edge.u == roads[i] && edge.v == roads[i + 1]) ||
                (edge.u == roads[i + 1] && edge.v == roads[i])) {
                total_weight += edge.weight;
                break;
            }
        }
    }
    return total_weight;
}

int get_point_distance(int p, const vector<int>& roads) {
    int min_dist = INT_MAX;
    for (const auto& node : roads) {
        vector<int> path;
        int dist = find_route(node, p, path);
        if(dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist;
}

int find_diameter() {
    int max_dist = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            vector<int> path;
            int dist = find_route(i, j, path);
            if (dist > max_dist)
                max_dist = dist;
        }
    }
    return max_dist;
}

int ECC(const vector<int>& roads) {
    int max_ecc = 0;
    for (int i = 0; i < n; ++i) {
        max_ecc = max(max_ecc, get_point_distance(i, roads));
    }
    return max_ecc;
}

int main() {
    cin >> n >> s;

    edges.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].u--;
        edges[i].v--;
    }

    int diameter = find_diameter();
    vector<int> dia_roads;
    int best_answer = ECC(dia_roads);
    cout << best_answer << endl;

    return 0;
}