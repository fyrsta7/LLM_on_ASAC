#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

const int MAXN = 2005;
const int MAXV = 305;
const int INF = 1e9;

int n, m, v, e;
int c[MAXN], d[MAXN];
double k[MAXN];
int dist[MAXV][MAXV];
double dp[MAXN][MAXN][2];

void floydWarshall() {
    for (int k = 1; k <= v; ++k) {
        for (int i = 1; i <= v; ++i) {
            for (int j = 1; j <= v; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    cin >> n >> m >> v >> e;
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i <= n; ++i) cin >> k[i];

    for (int i = 1; i <= v; ++i) {
        for (int j = 1; j <= v; ++j) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        dist[a][b] = dist[b][a] = min(dist[a][b], w);
    }

    floydWarshall();

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }

    dp[1][0][0] = dp[1][1][1] = 0;

    for (int i = 2; i <= n; ++i) {
        dp[i][0][0] = dp[i-1][0][0] + dist[c[i-1]][c[i]];
        for (int j = 1; j <= min(i, m); ++j) {
            dp[i][j][0] = min(dp[i-1][j][0] + dist[c[i-1]][c[i]],
                              dp[i-1][j][1] + k[i-1] * dist[d[i-1]][c[i]] + (1 - k[i-1]) * dist[c[i-1]][c[i]]);
            dp[i][j][1] = min(dp[i-1][j-1][0] + k[i] * dist[c[i-1]][d[i]] + (1 - k[i]) * dist[c[i-1]][c[i]],
                              dp[i-1][j-1][1] + k[i-1] * k[i] * dist[d[i-1]][d[i]] + k[i-1] * (1 - k[i]) * dist[d[i-1]][c[i]]
                              + (1 - k[i-1]) * k[i] * dist[c[i-1]][d[i]] + (1 - k[i-1]) * (1 - k[i]) * dist[c[i-1]][c[i]]);
        }
    }

    double ans = INF;
    for (int i = 0; i <= m; ++i) {
        ans = min(ans, min(dp[n][i][0], dp[n][i][1]));
    }

    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}
