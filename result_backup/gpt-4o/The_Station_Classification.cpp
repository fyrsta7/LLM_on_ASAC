#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> stops(m);
    set<int> levels;

    for (int i = 0; i < m; ++i) {
        int si;
        cin >> si;
        stops[i].resize(si);

        for (int j = 0; j < si; ++j) {
            cin >> stops[i][j];
            levels.insert(stops[i][j]);
        }
    }

    cout << levels.size() << endl;
    return 0;
}