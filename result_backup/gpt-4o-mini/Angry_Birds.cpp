#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Pig {
    double x, y;
};

bool is_killed(double a, double b, const Pig& pig) {
    return pig.y == a * pig.x * pig.x + b * pig.x;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<Pig> pigs(n);
        for (int i = 0; i < n; i++) {
            cin >> pigs[i].x >> pigs[i].y;
        }

        vector<int> dp(1 << n, 1e9);
        dp[0] = 0;

        for (int mask = 0; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) continue;

                vector<Pig> killed;
                double a = -1.0, b = 0.0;
                for (int j = 0; j < n; j++) {
                    if (!(mask & (1 << j))) {
                        if (killed.size() < 2) {
                            killed.push_back(pigs[j]);
                        }

                        if (killed.size() == 2) {
                            a = (killed[0].y - killed[1].y) / (killed[0].x * killed[0].x - killed[1].x * killed[1].x);
                            b = killed[0].y - a * killed[0].x * killed[0].x;
                            break;
                        }
                    }
                }

                if (killed.size() < 2) {
                    a = -(pigs[i].y / (pigs[i].x * pigs[i].x));
                    b = 0;
                }

                int new_mask = mask;
                for (int j = 0; j < n; j++) {
                    if (is_killed(a, b, pigs[j])) {
                        new_mask |= (1 << j);
                    }
                }
                dp[new_mask] = min(dp[new_mask], dp[mask] + 1);
            }
        }
        cout << dp[(1 << n) - 1] << endl;
    }
    return 0;
}