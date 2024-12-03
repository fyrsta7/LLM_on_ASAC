#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> wish1(n + 1), wish2(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> wish1[i] >> wish2[i];
    }

    vector<int> visited(n + 1, 0);
    int totalCost = 0;

    for (int i = 1; i <= n; ++i) {
        if (visited[i]) continue;

        vector<int> cycle;
        int x = i;

        while (!visited[x]) {
            visited[x] = 1;
            cycle.push_back(x);
            x = wish1[x] == x ? wish2[x] : wish1[x];
        }

        int cycleSize = cycle.size();
        bool validCycle = true;

        for (int j = 0; j < cycleSize; ++j) {
            int student = cycle[j];
            if (find(cycle.begin(), cycle.end(), wish1[student]) == cycle.end() &&
                find(cycle.begin(), cycle.end(), wish2[student]) == cycle.end()) {
                    validCycle = false;
                    break;
            }
        }

        if (!validCycle) {
            cout << -1 << endl;
            return 0;
        }

        totalCost += cycleSize;
    }

    cout << totalCost << endl;
    return 0;
}