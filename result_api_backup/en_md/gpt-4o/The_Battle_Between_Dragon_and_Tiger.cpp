#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> c(n+1);
    for(int i = 1; i <= n; ++i) {
        cin >> c[i];
    }

    int m, p1, s1, s2;
    cin >> m >> p1 >> s1 >> s2;

    long long dragonPower = 0, tigerPower = 0;
    for(int i = 1; i < m; ++i) {
        dragonPower += c[i] * (m - i);
    }
    for(int i = m + 1; i <= n; ++i) {
        tigerPower += c[i] * (i - m);
    }

    tigerPower += s1 * (p1 - m);

    long long minGap = LLONG_MAX;
    int bestP2 = 1;
    for(int i = 1; i <= n; ++i) {
        if (i < m) {
            long long newDragonPower = dragonPower + s2 * (m - i);
            long long gap = abs(newDragonPower - tigerPower);
            if (gap < minGap) {
                minGap = gap;
                bestP2 = i;
            }
        } else if (i > m) {
            long long newTigerPower = tigerPower + s2 * (i - m);
            long long gap = abs(dragonPower - newTigerPower);
            if (gap < minGap) {
                minGap = gap;
                bestP2 = i;
            }
        }
    }

    cout << bestP2 << endl;

    return 0;
}
