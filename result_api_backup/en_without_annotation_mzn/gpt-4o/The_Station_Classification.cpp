#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> s(m);
    vector<set<int>> pset(m);
    vector<int> level(n);
    vector<int> split(m), start(m), end(m);
    set<int> level_set;
    set<int> all_station;
    
    // Read input values
    for (int i = 0; i < m; ++i) cin >> s[i];
    for (int i = 0; i < m; ++i) {
        int size, x;
        cin >> size;
        for (int j = 0; j < size; ++j) {
            cin >> x;
            pset[i].insert(x);
        }
    }
    for (int i = 0; i < n; ++i) cin >> level[i];
    for (int i = 0; i < m; ++i) cin >> split[i];
    for (int i = 0; i < m; ++i) cin >> start[i];
    for (int i = 0; i < m; ++i) cin >> end[i];
    
    // Initialize all_station
    for (int i = 1; i <= n; ++i) all_station.insert(i);

    // Process constraints
    for (int i = 0; i < m; ++i) {
        for (const auto &station : pset[i]) {
            if (!(start[i] <= station && end[i] >= station)) {
                cout << "Constraints not satisfied" << endl;
                return 1;
            }
            if (!(level[station - 1] >= split[i])) {
                cout << "Constraints not satisfied" << endl;
                return 1;
            }
        }
        for (int station = start[i]; station <= end[i]; ++station) {
            if (pset[i].find(station) == pset[i].end()) {
                if (level[station - 1] >= split[i]) {
                    cout << "Constraints not satisfied" << endl;
                    return 1;
                }
            }
        }
    }

    // Find unique levels and minimize
    for (const auto &lv : level) {
        level_set.insert(lv);
    }
    int card_level_set = level_set.size();
    cout << card_level_set << endl;

    return 0;
}