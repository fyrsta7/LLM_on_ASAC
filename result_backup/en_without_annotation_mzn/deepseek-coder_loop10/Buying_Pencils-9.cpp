#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> pencil(3, vector<int>(2));
    for (int i = 0; i < 3; ++i) {
        cin >> pencil[i][0] >> pencil[i][1];
    }

    int max_single = 0;
    for (int i = 0; i < 3; ++i) {
        max_single = max(max_single, static_cast<int>(ceil(static_cast<double>(pencil[i][1]) / pencil[i][0])));
    }

    int min_cost = max_single * n;
    for (int i = 0; i < 3; ++i) {
        int cost = (n + pencil[i][0] - 1) / pencil[i][0] * pencil[i][1];
        min_cost = min(min_cost, cost);
    }

    cout << "cost=" << min_cost << endl;
    return 0;
}