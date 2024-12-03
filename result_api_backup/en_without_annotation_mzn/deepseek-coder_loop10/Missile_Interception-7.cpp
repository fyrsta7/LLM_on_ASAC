#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
    int x1, y1, x2, y2, N;
    cin >> x1 >> y1 >> x2 >> y2 >> N;
    vector<Point> positions(N);
    for (int i = 0; i < N; ++i) {
        cin >> positions[i].x >> positions[i].y;
    }

    Point p1 = {x1, y1}, p2 = {x2, y2};
    vector<double> dist1(N), dist2(N);
    for (int i = 0; i < N; ++i) {
        dist1[i] = dist(positions[i], p1);
        dist2[i] = dist(positions[i], p2);
    }

    double min_r1s = 0, min_r2s = 0;
    for (int i = 0; i < N; ++i) {
        min_r1s = max(min_r1s, dist1[i]);
        min_r2s = max(min_r2s, dist2[i]);
    }

    double result = min_r1s + min_r2s;
    for (int i = 0; i < N; ++i) {
        double r1s = dist1[i];
        double r2s = 0;
        for (int j = 0; j < N; ++j) {
            if (dist1[j] > r1s) {
                r2s = max(r2s, dist2[j]);
            }
        }
        result = min(result, r1s + r2s);
    }

    cout << static_cast<int>(ceil(result)) << endl;
    return 0;
}