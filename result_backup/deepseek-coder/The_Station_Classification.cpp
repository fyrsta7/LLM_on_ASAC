#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> trains(m);
    vector<int> levels(n, 0);
    int maxLevel = 0;

    for (int i = 0; i < m; ++i) {
        int si;
        cin >> si;
        trains[i].resize(si);
        for (int j = 0; j < si; ++j) {
            cin >> trains[i][j];
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 1; j < trains[i].size(); ++j) {
            int station = trains[i][j];
            int prevStation = trains[i][j - 1];
            if (station - prevStation > 1) {
                levels[station - 1] = max(levels[station - 1], levels[prevStation - 1] + 1);
            } else {
                levels[station - 1] = max(levels[station - 1], levels[prevStation - 1]);
            }
            maxLevel = max(maxLevel, levels[station - 1]);
        }
    }

    cout << maxLevel + 1 << endl;
    return 0;
}