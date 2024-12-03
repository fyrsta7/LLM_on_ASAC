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

void compute_size(int i) {
    int lsize = (l[i] == -1) ? 0 : size[l[i]];
    int rsize = (r[i] == -1) ? 0 : size[r[i]];
    size[i] = lsize + rsize + 1;
}

void compute_val(int root, int i) {
    if (vis[root][i] && a[root][i] > 0 && c[i] == c[a[root][i]]) {
        bool left_val = (l[i] == -1) || val[root][l[i]];
        bool right_val = (r[i] == -1) || val[root][r[i]];
        val[root][i] = left_val && right_val;
    } else {
        val[root][i] = false;
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

    for (int i = 1; i <= n; ++i) {
        a[i][i] = i;
        compute_size(i);
    }

    for (int root = 1; root <= n; ++root) {
        for (int i = 1; i <= n; ++i) {
            compute_val(root, i);
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
