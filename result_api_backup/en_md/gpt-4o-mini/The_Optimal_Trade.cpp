#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to;
    bool isBidirectional;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> prices(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> prices[i];

    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        graph[x].push_back({y, z == 2});
        if (z == 2) {
            graph[y].push_back({x, true});
        }
    }

    vector<int> maxProfit(n + 1, -1);
    queue<int> q;
    q.push(1);
    maxProfit[1] = 0;

    while (!q.empty()) {
        int city = q.front();
        q.pop();

        for (const auto& edge : graph[city]) {
            int nextCity = edge.to;
            int profit = prices[nextCity] - prices[city];

            if (profit > 0) {
                if (maxProfit[nextCity] < maxProfit[city] + profit) {
                    maxProfit[nextCity] = maxProfit[city] + profit;
                    q.push(nextCity);
                }
            }
        }
    }

    int result = maxProfit[n];
    cout << (result > 0 ? result : 0) << endl;

    return 0;
}