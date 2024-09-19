#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
    double dist1, dist2;
};

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int N;
    cin >> N;
    vector<Point> missiles(N);
    for (int i = 0; i < N; ++i) {
        cin >> missiles[i].x >> missiles[i].y;
        missiles[i].dist1 = distance(missiles[i].x, missiles[i].y, x1, y1);
        missiles[i].dist2 = distance(missiles[i].x, missiles[i].y, x2, y2);
    }

    sort(missiles.begin(), missiles.end(), [](const Point &a, const Point &b) {
        return a.dist1 < b.dist1;
    });

    double maxDist2 = 0;
    double minCost = missiles[N-1].dist1 * missiles[N-1].dist1;
    for (int i = N-1; i >= 0; --i) {
        maxDist2 = max(maxDist2, missiles[i].dist2);
        double cost = maxDist2 * maxDist2;
        if (i > 0) {
            cost += missiles[i-1].dist1 * missiles[i-1].dist1;
        }
        minCost = min(minCost, cost);
    }

    cout << static_cast<int>(minCost) << endl;
    return 0;
}
