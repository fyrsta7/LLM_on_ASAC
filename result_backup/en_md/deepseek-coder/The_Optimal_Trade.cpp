#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int to, type;
};

vector<int> prices;
vector<vector<Edge>> graph;
vector<int> minPrice;
vector<int> maxPrice;

void bfs(int start, vector<int>& priceArray) {
    queue<int> q;
    q.push(start);
    priceArray[start] = prices[start];
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge& e : graph[u]) {
            if (priceArray[e.to] > priceArray[u]) {
                priceArray[e.to] = priceArray[u];
                q.push(e.to);
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    prices.resize(n + 1);
    graph.resize(n + 1);
    minPrice.resize(n + 1, INT_MAX);
    maxPrice.resize(n + 1, INT_MIN);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &prices[i]);
    }

    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        graph[x].push_back({y, z});
        if (z == 2) {
            graph[y].push_back({x, z});
        }
    }

    bfs(1, minPrice);
    bfs(n, maxPrice);

    int maxProfit = 0;
    for (int i = 1; i <= n; ++i) {
        if (minPrice[i] != INT_MAX && maxPrice[i] != INT_MIN) {
            maxProfit = max(maxProfit, maxPrice[i] - minPrice[i]);
        }
    }

    printf("%d\n", maxProfit);
    return 0;
}
