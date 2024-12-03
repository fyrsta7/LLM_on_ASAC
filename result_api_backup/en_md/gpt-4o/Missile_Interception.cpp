#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int x1, y1, x2, y2, N;
    cin >> x1 >> y1 >> x2 >> y2;
    cin >> N;

    vector<pair<int, int>> missiles(N);
    for (int i = 0; i < N; ++i) {
        cin >> missiles[i].first >> missiles[i].second;
    }

    auto distanceSquared = [](int x1, int y1, int x2, int y2){
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    };
    
    vector<int> dist1(N), dist2(N);
    for (int i = 0; i < N; ++i) {
        dist1[i] = distanceSquared(x1, y1, missiles[i].first, missiles[i].second);
        dist2[i] = distanceSquared(x2, y2, missiles[i].first, missiles[i].second);
    }

    int minCost = INT_MAX;
    for (int radius1 : dist1) {
        int radius2 = 0;
        for (int i = 0; i < N; ++i) {
            if (dist1[i] > radius1) {
                radius2 = max(radius2, dist2[i]);
            }
        }
        minCost = min(minCost, radius1 + radius2);
    }

    cout << minCost << endl;

    return 0;
}
