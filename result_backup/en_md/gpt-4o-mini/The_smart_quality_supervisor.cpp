#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Ore {
    long long weight;
    long long value;
};

int main() {
    int n, m;
    long long s;
    cin >> n >> m >> s;

    vector<Ore> ores(n);
    for (int i = 0; i < n; ++i) {
        cin >> ores[i].weight >> ores[i].value;
    }

    vector<long long> prefixWeight(n + 1, 0);
    vector<long long> prefixValue(n + 1, 0);
    
    for (int i = 1; i <= n; ++i) {
        prefixWeight[i] = prefixWeight[i - 1] + ores[i - 1].weight;
        prefixValue[i] = prefixValue[i - 1] + ores[i - 1].value;
    }

    long long result = numeric_limits<long long>::max();

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        long long totalWeight = prefixWeight[r] - prefixWeight[l - 1];
        long long totalValue = prefixValue[r] - prefixValue[l - 1];
        long long testValue = totalWeight * totalValue;

        result = min(result, abs(s - testValue));
    }

    cout << result << endl;
    return 0;
}