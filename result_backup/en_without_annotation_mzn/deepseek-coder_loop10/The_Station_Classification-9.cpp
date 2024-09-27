#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> s(m);
    vector<vector<int>> pset(m);

    for (int i = 0; i < m; ++i) {
        cin >> s[i];
        pset[i].resize(s[i]);
        for (int j = 0; j < s[i]; ++j) {
            cin >> pset[i][j];
        }
    }

    vector<int> level(n, 1);
    vector<int> split(m, 1);
    vector<int> start(m, 1);
    vector<int> end(m, n);

    for (int i = 0; i < m; ++i) {
        start[i] = *min_element(pset[i].begin(), pset[i].end());
        end[i] = *max_element(pset[i].begin(), pset[i].end());
    }

    for (int i = 0; i < m; ++i) {
        split[i] = *max_element(pset[i].begin(), pset[i].end()) + 1;
        for (int station : pset[i]) {
            level[station - 1] = max(level[station - 1], split[i]);
        }
    }

    set<int> level_set;
    for (int l : level) {
        level_set.insert(l);
    }

    cout << level_set.size() << endl;

    return 0;
}
