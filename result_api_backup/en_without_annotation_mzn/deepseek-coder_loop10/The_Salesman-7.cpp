#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> S(n);
    vector<int> A(n);
    for (int i = 0; i < n; ++i) cin >> S[i];
    for (int i = 0; i < n; ++i) cin >> A[i];

    vector<int> dp(n + 1, 0);
    vector<int> r(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            int cost = dp[j - 1] + A[j - 1] + S[i - 1] * 2;
            if (cost > dp[i]) {
                dp[i] = cost;
                r[i] = j;
            }
        }
    }

    vector<int> c(n);
    for (int i = 1; i <= n; ++i) {
        c[i - 1] = dp[i] - dp[r[i] - 1];
    }

    for (int i = 0; i < n; ++i) {
        cout << c[i] << " ";
    }
    cout << endl;

    return 0;
}