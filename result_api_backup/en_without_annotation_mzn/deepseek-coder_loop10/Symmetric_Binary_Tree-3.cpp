#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> l, r, c;
vector<int> father;
vector<vector<int>> a;
vector<vector<bool>> vis, val;
vector<int> size;
int pos, ans;

void dfs(int root, int i) {
    vis[root][i] = true;
    if (l[i] != -1) dfs(root, l[i]);
    if (r[i] != -1) dfs(root, r[i]);
}

void pushup(int root, int i) {
    if (a[root][i] > 0) {
        vis[root][i] = true;
        if (i != root && father[a[root][i]] == a[root][father[i]]) {
            pushup(root, father[i]);
        }
    }
}

void pushdown(int root, int i) {
    int m = a[root][i];
    int l1 = l[i], l2 = l[m], r1 = r[i], r2 = r[m];
    if (a[root][m] == i && (l1 == -1 || a[root][l1] == r2) && (l2 == -1 || a[root][l2] == r1)) {
        if (l1 != -1) pushdown(root, l1);
        if (r1 != -1) pushdown(root, r1);
    }
}

void size_ok(int i) {
    int lsize = (l[i] == -1) ? 0 : size[l[i]];
    int rsize = (r[i] == -1) ? 0 : size[r[i]];
    size[i] = lsize + rsize + 1;
}

void check_val(int root, int i) {
    val[root][i] = vis[root][i] && a[root][i] > 0 && c[i] == c[a[root][i]];
    if (l[i] != -1) val[root][i] = val[root][i] && val[root][l[i]];
    if (r[i] != -1) val[root][i] = val[root][i] && val[root][r[i]];
}

int main() {
    cin >> n;
    l.resize(n + 1);
    r.resize(n + 1);
    c.resize(n + 1);
    father.resize(n + 1);
    a.assign(n + 1, vector<int>(n + 1, 0));
    vis.assign(n + 1, vector<bool>(n + 1, false));
    val.assign(n + 1, vector<bool>(n + 1, false));
    size.resize(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i] >> c[i];
        if (l[i] != -1) father[l[i]] = i;
        if (r[i] != -1) father[r[i]] = i;
    }

    for (int root = 1; root <= n; ++root) {
        dfs(root, root);
        for (int i = 1; i <= n; ++i) {
            pushup(root, i);
            pushdown(root, i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        size_ok(i);
    }

    for (int root = 1; root <= n; ++root) {
        for (int i = 1; i <= n; ++i) {
            check_val(root, i);
        }
    }

    cin >> pos;
    ans = val[pos][pos] ? size[pos] : 0;
    cout << ans << endl;

    return 0;
}
