#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> sappers(n);
    for (int i = 0; i < n; ++i) {
        cin >> sappers[i];
    }
    
    int m, p1, s1, s2;
    cin >> m >> p1 >> s1 >> s2;
    
    // 1-based index adjustment
    m--;
    p1--;

    // Calculate initial power
    long long dragonPower = 0, tigerPower = 0;

    for (int i = 0; i < m; ++i) {
        dragonPower += sappers[i] * (m - i);
    }
    for (int i = m + 1; i < n; ++i) {
        tigerPower += sappers[i] * (i - m);
    }
    dragonPower += sappers[p1] * (m - p1) + s1 * (m - p1);
    tigerPower += s1 * (p1 - m);

    long long minGap = numeric_limits<long long>::max();
    int bestP2 = -1;

    for (int p2 = 0; p2 < n; ++p2) {
        if (p2 == m) continue; // Can't send to m
        
        long long newDragonPower = dragonPower;
        long long newTigerPower = tigerPower;

        if (p2 < m) {
            newDragonPower += s2 * (m - p2);
        } else {
            newTigerPower += s2 * (p2 - m);
        }

        long long currentGap = abs(newDragonPower - newTigerPower);
        if (currentGap < minGap) {
            minGap = currentGap;
            bestP2 = p2 + 1; // convert to 1-based index
        } else if (currentGap == minGap) {
            bestP2 = min(bestP2, p2 + 1); // ensure smallest index
        }
    }
    
    cout << bestP2 << endl;
    return 0;
}