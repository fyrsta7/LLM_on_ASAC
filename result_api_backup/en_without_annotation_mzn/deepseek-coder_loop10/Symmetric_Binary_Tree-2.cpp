#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int l, r, c;
};

int n;
vector<Node> tree;
vector<int> size;
vector<vector<int>> a;
vector<vector<bool>> vis;
vector<vector<bool>> val;

void dfs(int root, int i) {
    vis[root][i] = true;
    if (tree[i].l != -1) dfs(root, tree[i].l);
    if (tree[i].r != -1) dfs(root, tree[i].r);
}

void build_vis() {
    vis.assign(n + 1, vector<bool>(n + 1, false));
    for (int i = 1; i <= n; ++i) {
        dfs(i, i);
    }
}

void build_a() {
    a.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        a[i][i] = i;
    }
    for (int root = 1; root <= n; ++root) {
        for (int i = 1; i <= n; ++i) {
            if (vis[root][i]) {
                if (tree[i].l != -1 && vis[root][tree[i].l]) {
                    a[root][tree[i].l] = tree[i].r;
                    a[root][tree[i].r] = tree[i].l;
                }
            }
        }
    }
}

void build_size() {
    size.assign(n + 1, 0);
    for (int i = n; i >= 1; --i) {
        size[i] = 1;
        if (tree[i].l != -1) size[i] += size[tree[i].l];
        if (tree[i].r != -1) size[i] += size[tree[i].r];
    }
}

void build_val() {
    val.assign(n + 1, vector<bool>(n + 1, false));
    for (int root = 1; root <= n; ++root) {
        for (int i = 1; i <= n; ++i) {
            if (vis[root][i] && a[root][i] > 0 && tree[i].c == tree[a[root][i]].c) {
                val[root][i] = true;
                if (tree[i].l != -1) val[root][i] = val[root][i] && val[root][tree[i].l];
                if (tree[i].r != -1) val[root][i] = val[root][i] && val[root][tree[i].r];
            }
        }
    }
}

int main() {
    cin >> n;
    tree.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> tree[i].l >> tree[i].r >> tree[i].c;
    }

    build_vis();
    build_a();
    build_size();
    build_val();

    int pos;
    cin >> pos;

    int ans = 0;
    if (val[pos][pos]) {
        ans = size[pos];
    }

    cout << ans << endl;

    return 0;
}
