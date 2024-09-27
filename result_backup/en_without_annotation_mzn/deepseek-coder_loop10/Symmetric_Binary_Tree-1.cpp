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

void build_tree() {
    for (int i = 1; i <= n; ++i) {
        if (l[i] != -1) father[l[i]] = i;
        if (r[i] != -1) father[r[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        dfs(i, i);
    }
}

void calculate_size(int i) {
    size[i] = 1;
    if (l[i] != -1) {
        calculate_size(l[i]);
        size[i] += size[l[i]];
    }
    if (r[i] != -1) {
        calculate_size(r[i]);
        size[i] += size[r[i]];
    }
}

void check_val(int root, int i) {
    if (vis[root][i] && a[root][i] > 0 && c[i] == c[a[root][i]]) {
        val[root][i] = true;
        if (l[i] != -1) check_val(root, l[i]);
        if (r[i] != -1) check_val(root, r[i]);
    }
}

int main() {
    cin >> n;
    l.resize(n + 1);
    r.resize(n + 1);
    c.resize(n + 1);
    father.resize(n + 1);
    size.resize(n + 1);
    a.assign(n + 1, vector<int>(n + 1, 0));
    vis.assign(n + 1, vector<bool>(n + 1, false));
    val.assign(n + 1, vector<bool>(n + 1, false));

    for (int i = 1; i <= n; ++i) cin >> l[i];
    for (int i = 1; i <= n; ++i) cin >> r[i];
    for (int i = 1; i <= n; ++i) cin >> c[i];

    build_tree();
    calculate_size(1);

    for (int root = 1; root <= n; ++root) {
        for (int i = 1; i <= n; ++i) {
            if (vis[root][i]) {
                a[root][i] = i;
                if (l[i] != -1) a[root][l[i]] = r[i];
                if (r[i] != -1) a[root][r[i]] = l[i];
            }
        }
    }

    for (int root = 1; root <= n; ++root) {
        for (int i = 1; i <= n; ++i) {
            check_val(root, i);
        }
    }

    ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (val[i][i]) {
            ans = max(ans, size[i]);
        }
    }

    cout << ans << endl;
    return 0;
}
