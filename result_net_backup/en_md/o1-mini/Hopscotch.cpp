#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Square {
    int x, s;
};

int main() {
    int n, d, k;
    cin >> n >> d >> k;

    vector<Square> squares(n);
    for (int i = 0; i < n; ++i) {
        cin >> squares[i].x >> squares[i].s;
    }

    // dp[i][g] will store the maximum score we can obtain from the i-th square
    // with the robot's flexibility improved by g gold coins.
    vector<vector<int>> dp(n + 1, vector<int>(d + 1001, -1));
    dp[0][d] = 0;  // Starting point at the first square with no gold spent

    for (int i = 1; i <= n; ++i) {
        for (int g = 0; g <= d; ++g) {
            if (dp[i - 1][g] == -1) continue;

            // Calculate possible steps from current square with current flexibility
            int max_step = d + g;
            for (int step = max(1, d - g); step <= max_step; ++step) {
                int next_pos = squares[i - 1].x + step;
                if (next_pos <= squares[n - 1].x) {
                    dp[i][g + 1] = max(dp[i][g + 1], dp[i - 1][g] + squares[i - 1].s);
                }
            }
        }
    }

    int result = -1;
    for (int g = 0; g <= d; ++g) {
        if (dp[n][g] >= k) {
            result = g;
            break;
        }
    }

    cout << result << endl;

    return 0;
}