#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXM = 100;
const int MAXT = 10;
const int INF = 1e9;

int L, S, T, M;
int pebbles[MAXM + 1];
int dp[MAXM * MAXT + 1];

int main() {
    cin >> L >> S >> T >> M;
    for (int i = 0; i < M; ++i) {
        cin >> pebbles[i];
    }
    if (S == T) {
        int count = 0;
        for (int i = 0; i < M; ++i) {
            if (pebbles[i] % S == 0) {
                count++;
            }
        }
        cout << count << endl;
        return 0;
    }
    sort(pebbles, pebbles + M);
    vector<int> compressed;
    int prev = 0;
    for (int i = 0; i < M; ++i) {
        int diff = pebbles[i] - prev;
        if (diff > MAXM * MAXT) diff = MAXM * MAXT;
        prev = pebbles[i];
        pebbles[i] = pebbles[i - 1] + diff;
        compressed.push_back(pebbles[i]);
    }
    L = pebbles[M - 1] + MAXM * MAXT;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= L; ++i) {
        for (int j = S; j <= T; ++j) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + binary_search(compressed.begin(), compressed.end(), i));
            }
        }
    }
    int ans = INF;
    for (int i = pebbles[M - 1]; i <= L; ++i) {
        ans = min(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
