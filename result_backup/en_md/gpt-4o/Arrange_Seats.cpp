#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    int u, v, weight;
};

struct Subset {
    int parent, rank;
};

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int main() {
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;
    
    vector<Edge> edges;
    for (int i = 0; i < D; ++i) {
        int Xi, Yi, Pi, Qi;
        cin >> Xi >> Yi >> Pi >> Qi;
        if (Xi == Pi) {
            edges.push_back({(Xi-1)*N + Yi-1, (Pi-1)*N + Qi-1, 1});
        } else {
            edges.push_back({(Xi-1)*N + Yi-1, (Pi-1)*N + Qi-1, 1});
        }
    }
    
    sort(edges.begin(), edges.end(), compare);
    
    Subset* subsets = new Subset[M*N];
    for (int v = 0; v < M*N; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    vector<int> rowCuts, colCuts;
    
    for (auto& edge : edges) {
        int x = find(subsets, edge.u);
        int y = find(subsets, edge.v);
        if (x != y) {
            Union(subsets, x, y);
            int u = edge.u, v = edge.v;
            int row_u = u / N, col_u = u % N;
            int row_v = v / N, col_v = v % N;
            if (row_u == row_v) {
                colCuts.push_back(min(col_u, col_v) + 1);
            } else {
                rowCuts.push_back(min(row_u, row_v) + 1);
            }
        }
    }
    
    sort(rowCuts.begin(), rowCuts.end());
    sort(colCuts.begin(), colCuts.end());
    
    for (int i = 0; i < K; ++i) {
        if (i > 0) cout << " ";
        cout << rowCuts[i];
    }
    cout << endl;
    for (int i = 0; i < L; ++i) {
        if (i > 0) cout << " ";
        cout << colCuts[i];
    }
    cout << endl;
    
    delete[] subsets;
    return 0;
}