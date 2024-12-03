#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll x, y, z, b1, b2, m;
vector<ll> p, l, r;

void generate_ai(int n, vector<ll>& a) {
    a.resize(n);
    vector<ll> b(n);
    b[0] = b1;
    b[1] = b2;
    for (int i = 2; i < n; ++i) {
        b[i] = (x * b[i - 1] + y * b[i - 2] + z) % (1LL << 30);
    }
    for (int j = 0; j < p.size(); ++j) {
        for (int i = p[j] - 1; i >= (j > 0 ? p[j - 1] : 0); --i) {
            a[i] = (b[i] % (r[j] - l[j] + 1)) + l[j];
        }
    }
}

ll solve(int n, vector<ll>& a) {
    vector<ll> prefix_sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + a[i - 1];
    }

    vector<ll> dp(n + 1, 1LL << 62);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] = min(dp[i], dp[j] + (prefix_sum[i] - prefix_sum[j]) * (prefix_sum[i] - prefix_sum[j]));
        }
    }

    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, type;
    cin >> n >> type;

    vector<ll> a;
    if (type == 0) {
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
    } else {
        cin >> x >> y >> z >> b1 >> b2 >> m;
        p.resize(m);
        l.resize(m);
        r.resize(m);
        for (int i = 0; i < m; ++i) {
            cin >> p[i] >> l[i] >> r[i];
        }
        generate_ai(n, a);
    }

    cout << solve(n, a) << endl;

    return 0;
}
