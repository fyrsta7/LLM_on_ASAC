#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> s(m);
    vector<set<int>> pset(m);
    for (int i = 0; i < m; ++i) {
        cin >> s[i];
        for (int j = 0; j < s[i]; ++j) {
            int station;
            cin >> station;
            pset[i].insert(station);
        }
    }

    vector<int> level(n, 1);
    vector<int> split(m, 1);
    vector<int> start(m, 1);
    vector<int> end(m, n);

    for (int i = 0; i < m; ++i) {
        for (int station : pset[i]) {
            start[i] = min(start[i], station);
            end[i] = max(end[i], station);
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int station : pset[i]) {
            level[station - 1] = max(level[station - 1], split[i]);
        }
        for (int station = start[i]; station <= end[i]; ++station) {
            if (pset[i].find(station) == pset[i].end()) {
                level[station - 1] = min(level[station - 1], split[i] - 1);
            }
        }
    }

    set<int> level_set(level.begin(), level.end());
    cout << level_set.size() << endl;

    return 0;
}
