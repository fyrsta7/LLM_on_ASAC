#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int findSmallestM(vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;
    int g = a[0];
    for (int i = 1; i < n; ++i) {
        g = gcd(g, a[i]);
    }
    if (g != 1) return 1;
    sort(a.begin(), a.end());
    vector<bool> dp(a[n-1] + 1, false);
    dp[0] = true;
    for (int i = 0; i < n; ++i) {
        for (int j = a[i]; j <= a[n-1]; ++j) {
            if (dp[j - a[i]]) dp[j] = true;
        }
    }
    int count = 0;
    for (int i = 0; i <= a[n-1]; ++i) {
        if (!dp[i]) count++;
    }
    return count == 0 ? n : count;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        cout << findSmallestM(a) << endl;
    }
    return 0;
}
