```
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int l, r, c, size, father;
    bool val;
    Node() : l(-1), r(-1), c(0), size(1), father(0), val(true) {}
};

void dfs_size(vector<Node>& nodes, int i) {
    nodes[i].size = 1;
    if (nodes[i].l != -1) {
        dfs_size(nodes, nodes[i].l);
        nodes[i].size += nodes[nodes[i].l].size;
    }
    if (nodes[i].r != -1) {
        dfs_size(nodes, nodes[i].r);
        nodes[i].size += nodes[nodes[i].r].size;
    }
}

bool dfs_val(vector<Node>& nodes, int root, int i) {
    if (i == -1) return true;
    if (!nodes[i].val) return nodes[i].val;
    nodes[i].val = (nodes[i].c == nodes[root].c);
    nodes[i].val &= dfs_val(nodes, root, nodes[i].l);
    nodes[i].val &= dfs_val(nodes, root, nodes[i].r);
    return nodes[i].val;
}

int main() {
    int n;
    cin >> n;
    vector<Node> nodes(n + 1);

    for (int i = 1; i <= n; ++i)
        cin >> nodes[i].l >> nodes[i].r >> nodes[i].c;
    
    for (int i = 1; i <= n; ++i) {
        if (nodes[i].l != -1) nodes[nodes[i].l].father = i;
        if (nodes[i].r != -1) nodes[nodes[i].r].father = i;
    }

    dfs_size(nodes, 1); // assuming root is 1
    
    int ans = 0, pos = 1;
    for (int i = 1; i <= n; ++i) {
        nodes[i].val = dfs_val(nodes, i, i);
        if (nodes[i].val && nodes[i].size > ans) {
            ans = nodes[i].size;
            pos = i;
        }
    }
    
    cout << ans << endl;
    return 0;
}
