#include <iostream>
#include <vector>
#include <limits>
using namespace std;

typedef long long ll;

void solve_type_0(int n, const vector<int>& a) {
    vector<ll> dp(n + 1, LLONG_MAX);
    vector<ll> sum(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i - 1];
    }
    
    dp[0] = 0;  // Base case: no elements

    for (int j = 1; j <= n; j++) {
        for (int i = 0; i < j; i++) {
            if (sum[i] <= sum[j]) {
                dp[j] = min(dp[j], dp[i] + sum[j] * sum[j]);
            }
        }
    }
    
    cout << dp[n] << endl;
}

void generate_data(int n, int x, int y, int z, int b1, int b2, int m, vector<int>& a) {
    vector<int> b(n);
    b[0] = b1;
    b[1] = b2;
    
    for (int i = 2; i < n; i++) {
        b[i] = (x * b[i - 1] + y * b[i - 2] + z) % (1 << 30);
    }
    
    a.resize(n);
    int current_index = 0;
    for (int j = 0; j < m; j++) {
        int pi, li, ri;
        cin >> pi >> li >> ri;
        for (int k = current_index; k < pi; k++) {
            a[k] = (b[k] % (ri - li + 1)) + li;
        }
        current_index = pi;
    }
}

void solve_type_1(int n) {
    int x, y, z, b1, b2, m;
    cin >> x >> y >> z >> b1 >> b2 >> m;
    
    vector<int> a;
    generate_data(n, x, y, z, b1, b2, m, a);
    
    solve_type_0(n, a);
}

int main() {
    int n, type;
    cin >> n >> type;
    
    if (type == 0) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        solve_type_0(n, a);
    } else {
        solve_type_1(n);
    }
    
    return 0;
}