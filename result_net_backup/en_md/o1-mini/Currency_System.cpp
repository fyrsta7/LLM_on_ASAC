#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int solve(vector<int>& a) {
    int n = a.size();
    int g = a[0];
    for (int i = 1; i < n; i++) {
        g = gcd(g, a[i]);
    }
    if (g == 1) {
        return n;
    }
    vector<int> b;
    for (int i = 0; i < n; i++) {
        if (a[i] % g != 0) {
            b.push_back(a[i]);
        }
    }
    return b.size();
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << solve(a) << endl;
    }
    return 0;
}