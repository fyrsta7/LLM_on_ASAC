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
    vector<int> c(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            int cost = dp[i - j] + A[j - 1] + S[j - 1] * 2;
            if (cost > dp[i]) {
                dp[i] = cost;
                r[i] = j;
                c[i] = cost;
            }
        }
    }

    cout << "[";
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ", ";
        cout << c[i];
    }
    cout << "]" << endl;

    return 0;
}