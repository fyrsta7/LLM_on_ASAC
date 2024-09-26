#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

void generate_a(int n, int x, int y, int z, int b1, int b2, vector<int>& a, vector<tuple<int, int, int>>& constraints) {
    vector<int> b(n + 1);
    b[1] = b1;
    b[2] = b2;
    for (int i = 3; i <= n; ++i) {
        b[i] = ((long long) x * b[i - 1] + (long long) y * b[i - 2] + z) % (1 << 30);
    }

    int curr_constraint = 0;
    for (int i = 1; i <= n; ++i) {
        while (i > get<0>(constraints[curr_constraint])) {
            ++curr_constraint;
        }
        int l = get<1>(constraints[curr_constraint]);
        int r = get<2>(constraints[curr_constraint]);
        a[i] = (b[i] % (r - l + 1)) + l;
    }
}

int64_t min_cost(vector<int>& a) {
    int n = a.size();
    vector<int64_t> dp(n + 1, LLONG_MAX);
    dp[0] = 0;

    vector<int64_t> sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] != LLONG_MAX && (j == 0 || sum[i] - sum[j] >= sum[j] - sum[0])) {
                dp[i] = min(dp[i], dp[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]));
            }
        }
    }
    return dp[n];
}

int main() {
    int n, type;
    cin >> n >> type;
    
    vector<int> a(n + 1);
    
    if (type == 0) {
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
    } else {
        int x, y, z, b1, b2, m;
        cin >> x >> y >> z >> b1 >> b2 >> m;

        vector<tuple<int, int, int>> constraints(m);
        for (int i = 0; i < m; ++i) {
            int pi, li, ri;
            cin >> pi >> li >> ri;
            constraints[i] = {pi, li, ri};
        }
        
        generate_a(n, x, y, z, b1, b2, a, constraints);
    }
    
    cout << min_cost(a) << endl;
    
    return 0;
}