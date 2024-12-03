#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1e9;

struct Pipe {
    int pos, low, high;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> rise(n), fall(n);
    for (int i = 0; i < n; ++i) {
        cin >> rise[i] >> fall[i];
    }
    
    vector<vector<int>> pipes(n);
    for (int i = 0; i < k; ++i) {
        int pos, low, high;
        cin >> pos >> low >> high;
        pipes[pos].push_back(low);
        pipes[pos].push_back(high);
    }
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int height = 0; height <= m; ++height) {
            if (dp[i][height] == INF) continue;

            for (int click = 0; (click * rise[i]) + height <= m; ++click) {
                int new_height = height + (click * rise[i]) - fall[i];
                if (new_height < 0) break;

                bool hit_pipe = false;
                for (int j = 0; j < pipes[i].size(); j += 2) {
                    if (new_height >= pipes[i][j] && new_height <= pipes[i][j + 1]) {
                        hit_pipe = true;
                        break;
                    }
                }

                if (!hit_pipe && new_height <= m) {
                    dp[i + 1][new_height] = min(dp[i + 1][new_height], dp[i][height] + click);
                }
            }
        }
    }
    
    int min_taps = INF;
    for (int height = 1; height <= m; ++height) {
        min_taps = min(min_taps, dp[n][height]);
    }

    if (min_taps == INF) {
        int max_pipes = 0;
        for (int i = 0; i <= n; ++i) {
            for (int height = 1; height <= m; ++height) {
                if (dp[i][height] != INF) {
                    max_pipes = max(max_pipes, i);
                }
            }
        }
        cout << "0\n" << max_pipes << endl;
    } else {
        cout << "1\n" << min_taps << endl;
    }
    
    return 0;
}
