#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    int pencil[3][2];
    cin >> n;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> pencil[i][j];
        }
    }

    int max_single = 0;
    for (int i = 0; i < 3; ++i) {
        max_single = max(max_single, (int)ceil((double)pencil[i][1] / pencil[i][0]));
    }

    int min_cost = max_single * n;
    for (int i = 0; i < 3; ++i) {
        int cost = (int)ceil((double)n / pencil[i][0]) * pencil[i][1];
        min_cost = min(min_cost, cost);
    }

    cout << "cost=" << min_cost << endl;
    return 0;
}