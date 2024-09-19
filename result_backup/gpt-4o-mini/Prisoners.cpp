#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Conflict {
    int a, b, c;
};

bool cmp(const Conflict &x, const Conflict &y) {
    return x.c > y.c;
}

int findParent(int x, vector<int> &parent) {
    if (parent[x] != x) {
        parent[x] = findParent(parent[x], parent);
    }
    return parent[x];
}

void unionSets(int x, int y, vector<int> &parent) {
    int rootX = findParent(x, parent);
    int rootY = findParent(y, parent);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<Conflict> conflicts(M);
    for (int i = 0; i < M; i++) {
        cin >> conflicts[i].a >> conflicts[i].b >> conflicts[i].c;
    }
    
    sort(conflicts.begin(), conflicts.end(), cmp);
    
    vector<int> parent(N + 1);
    iota(parent.begin(), parent.end(), 0);
    
    int maxImpact = 0;
    
    for (int i = 0; i < M; i++) {
        int a = conflicts[i].a;
        int b = conflicts[i].b;
        if (findParent(a, parent) != findParent(b, parent)) {
            unionSets(a, b, parent);
        } else {
            maxImpact = conflicts[i].c;
            break;
        }
    }
    
    cout << maxImpact << endl;

    return 0;
}