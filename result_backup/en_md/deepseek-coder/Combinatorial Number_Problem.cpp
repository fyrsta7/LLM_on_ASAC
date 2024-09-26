#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2001;
vector<vector<int>> comb(MAXN, vector<int>(MAXN, 1));

void precompute(int k) {
    for (int i = 2; i < MAXN; ++i) {
        for (int j = 1; j < i; ++j) {
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % k;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, k;
    cin >> t >> k;

    precompute(k);

    vector<vector<int>> count(MAXN, vector<int>(MAXN, 0));
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j <= i; ++j) {
            count[i][j] = (comb[i][j] == 0);
            if (j > 0) count[i][j] += count[i][j-1];
        }
    }

    while (t--) {
        int n, m;
        cin >> n >> m;
        int ans = 0;
        for (int i = 0; i <= n; ++i) {
            int j = min(i, m);
            ans += count[i][j];
        }
        cout << ans << '\n';
    }

    return 0;
}
