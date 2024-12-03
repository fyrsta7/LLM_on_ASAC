#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

struct Road {
    int u, v, type;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }

    vector<Road> roads(m);
    for (int i = 0; i < m; ++i) {
        cin >> roads[i].u >> roads[i].v >> roads[i].type;
    }

    // We use Bellman-Ford algorithm for finding maximum income path
    vector<int> max_profit(n + 1, INT_MIN);
    max_profit[1] = 0;
    vector<int> buy_at(n + 1, INT_MIN);
    buy_at[1] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = roads[j].u;
            int v = roads[j].v;
            int type = roads[j].type;

            if (max_profit[u] != INT_MIN) {
                if (type == 2 || type == 0) {
                    if (max_profit[v] < max_profit[u] + price[v] - price[buy_at[u]]) {
                        max_profit[v] = max_profit[u] + price[v] - price[buy_at[u]];
                        buy_at[v] = buy_at[u];
                    }
                }
                if (max_profit[v] < -price[v]) {
                    max_profit[v] = -price[v];
                    buy_at[v] = v;
                }
            }

            if (max_profit[v] != INT_MIN) {
                if (type == 2 || type == 1) {
                    if (max_profit[u] < max_profit[v] + price[u] - price[buy_at[v]]) {
                        max_profit[u] = max_profit[v] + price[u] - price[buy_at[v]];
                        buy_at[u] = buy_at[v];
                    }
                }
                if (max_profit[u] < -price[u]) {
                    max_profit[u] = -price[u];
                    buy_at[u] = u;
                }
            }
        }
    }

    int income = max(0, max_profit[n]);
    cout << income << endl;

    return 0;
}