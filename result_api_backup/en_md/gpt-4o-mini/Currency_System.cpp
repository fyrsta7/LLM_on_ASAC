#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int findMinimalM(const vector<int>& a) {
    int n = a.size();
    if (n == 1) return 1; // only one denomination
    int g = a[0];
    for (int i = 1; i < n; i++) {
        g = gcd(g, a[i]);
    }
    int count = 0;
    for (int i = 1; i <= g; i++) {
        if (g % i == 0) count++;
    }
    return count;
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
        cout << findMinimalM(a) << endl;
    }

    return 0;
}