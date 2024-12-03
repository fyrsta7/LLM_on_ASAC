#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }
    vector<vector<pair<int, int>>> roads(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        roads[u].emplace_back(v, t);
        roads[v].emplace_back(u, t);
    }

    vector<int> min_price(n + 1, INT_MAX);
    vector<int> max_income(n + 1, INT_MIN);
    vector<bool> visited(n + 1, false);

    min_price[1] = price[1];
    max_income[1] = 0;

    for (int step = 0; step < n; ++step) {
        int u = -1;
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && (u == -1 || min_price[i] < min_price[u])) {
                u = i;
            }
        }

        visited[u] = true;
        for (auto& road : roads[u]) {
            int v = road.first;
            int t = road.second;
            int new_min_price = min_price[u];
            if (t == 2) {
                new_min_price = min(new_min_price, price[v]);
            }
            if (new_min_price < min_price[v]) {
                min_price[v] = new_min_price;
                max_income[v] = max_income[u];
            } else if (new_min_price == min_price[v]) {
                max_income[v] = max(max_income[v], max_income[u]);
            }
            if (price[v] > min_price[v]) {
                max_income[v] = max(max_income[v], price[v] - min_price[v]);
            }
        }
    }

    int income = max_income[n];
    cout << (income < 0 ? 0 : income) << endl;

    return 0;
}