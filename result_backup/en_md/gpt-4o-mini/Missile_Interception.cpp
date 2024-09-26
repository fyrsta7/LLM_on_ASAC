#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int N;
    cin >> N;

    vector<int> r1_sq(N), r2_sq(N);
    
    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        r1_sq[i] = (x1 - x) * (x1 - x) + (y1 - y) * (y1 - y);
        r2_sq[i] = (x2 - x) * (x2 - x) + (y2 - y) * (y2 - y);
    }

    int min_cost = INT_MAX;

    for (int i = 0; i <= N; ++i) {
        int r1 = *max_element(r1_sq.begin(), r1_sq.begin() + i);
        int r2 = *max_element(r2_sq.begin() + i, r2_sq.end());
        min_cost = min(min_cost, r1 + r2);
    }

    cout << min_cost << endl;
    return 0;
}