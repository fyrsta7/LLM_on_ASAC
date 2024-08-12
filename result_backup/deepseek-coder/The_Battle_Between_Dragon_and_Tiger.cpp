#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> c(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    int m, p1, s1, s2;
    cin >> m >> p1 >> s1 >> s2;

    vector<long long> power(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (i < m) {
            power[i] = c[i] * (m - i);
        } else if (i > m) {
            power[i] = c[i] * (i - m);
        }
    }

    long long dragonPower = 0, tigerPower = 0;
    for (int i = 1; i < m; ++i) {
        dragonPower += power[i];
    }
    for (int i = m + 1; i <= n; ++i) {
        tigerPower += power[i];
    }

    dragonPower += s1 * (abs(p1 - m));

    long long minDiff = abs(dragonPower - tigerPower);
    int bestP2 = 1;

    for (int p2 = 1; p2 <= n; ++p2) {
        if (p2 == m) continue;
        long long newDragonPower = dragonPower;
        long long newTigerPower = tigerPower;
        if (p2 < m) {
            newDragonPower += s2 * (m - p2);
        } else {
            newTigerPower += s2 * (p2 - m);
        }
        long long newDiff = abs(newDragonPower - newTigerPower);
        if (newDiff < minDiff || (newDiff == minDiff && p2 < bestP2)) {
            minDiff = newDiff;
            bestP2 = p2;
        }
    }

    cout << bestP2 << endl;
    return 0;
}
