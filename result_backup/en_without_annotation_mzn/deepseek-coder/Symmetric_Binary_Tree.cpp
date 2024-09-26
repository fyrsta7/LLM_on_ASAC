#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> l, r, c, father, size;
vector<vector<int>> a;
vector<vector<bool>> vis, val;
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

bool match(int root, int k1, int k2) {
    if (k1 == -1) return k2 == -1 || a[root][k2] == 0;
    if (k2 == -1) return k1 == -1 || a[root][k1] == 0;
    return a[root][k1] == k2 && a[root][k2] == k1;
}

void pushdown(int root, int i) {
    int m = a[root][i];
    int l1 = l[i], l2 = l[m], r1 = r[i], r2 = r[m];
    if (a[root][m] == i && match(root, l1, r2) && match(root, l2, r1)) {
        if (l1 != -1) pushdown(root, l1);
        if (r1 != -1) pushdown(root, r1);
        if (l2 != -1) pushdown(root, l2);
        if (r2 != -1) pushdown(root, r2);
    }
}

void size_ok(int i) {
    int lsize = (l[i] == -1) ? 0 : size[l[i]];
    int rsize = (r[i] == -1) ? 0 : size[r[i]];
    size[i] = lsize + rsize + 1;
}

bool check_val(int root, int i) {
    if (!vis[root][i] || a[root][i] <= 0 || c[i] != c[a[root][i]]) return false;
    if (l[i] != -1 && !check_val(root, l[i])) return false;
    if (r[i] != -1 && !check_val(root, r[i])) return false;
    return true;
}

int main() {
    cin >> n;
    l.resize(n + 1, -1);
    r.resize(n + 1, -1);
    c.resize(n + 1);
    father.resize(n + 1, 0);
    size.resize(n + 1, 1);
    a.assign(n + 1, vector<int>(n + 1, 0));
    vis.assign(n + 1, vector<bool>(n + 1, false));
    val.assign(n + 1, vector<bool>(n + 1, false));

    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i] >> c[i];
        if (l[i] != -1) father[l[i]] = i;
        if (r[i] != -1) father[r[i]] = i;
    }

    for (int i = 1; i <= n; ++i) {
        dfs(i, i);
        a[i][i] = i;
    }

    for (int root = 1; root <= n; ++root) {
        for (int i = 1; i <= n; ++i) {
            if (a[root][i] > 0) {
                pushup(root, i);
                pushdown(root, i);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        size_ok(i);
    }

    for (int root = 1; root <= n; ++root) {
        for (int i = 1; i <= n; ++i) {
            val[root][i] = check_val(root, i);
        }
    }

    cin >> pos;
    ans = val[pos][pos] ? size[pos] : 0;
    cout << ans << endl;

    return 0;
}
