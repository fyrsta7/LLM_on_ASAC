#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Pig {
    double x, y;
};

bool passThrough(Pig a, Pig b, Pig c) {
    double det = a.x * (b.y - c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);
    return fabs(det) < 1e-9;
}

int minBirds(int n, vector<Pig>& pigs) {
    if (n == 0) return 0;

    int min_count = n;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int birdsUsed = 0;
            vector<bool> killed(n, false);

            for (int k = 0; k < n; ++k) {
                if (!killed[k] && passThrough(pigs[i], pigs[j], pigs[k])) {
                    for (int l = 0; l < n; ++l) {
                        if (passThrough(pigs[i], pigs[j], pigs[l])) {
                            killed[l] = true;
                        }
                    }
                    birdsUsed++;
                }
            }
            min_count = min(min_count, birdsUsed);
        }
    }
    return min_count;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<Pig> pigs(n);
        for (int i = 0; i < n; ++i) {
            cin >> pigs[i].x >> pigs[i].y;
        }
        if (m == 1) {
            cout << (n + 2) / 3 << endl;
        } else if (m == 2) {
            cout << max(1, minBirds(n, pigs)) << endl;
        } else {
            cout << minBirds(n, pigs) << endl;
        }
    }
    return 0;
}