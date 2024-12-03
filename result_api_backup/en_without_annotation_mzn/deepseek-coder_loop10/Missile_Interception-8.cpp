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

    Point p1 = {x1, y1};
    Point p2 = {x2, y2};

    vector<double> dist1(N), dist2(N);
    for (int i = 0; i < N; ++i) {
        dist1[i] = dist(positions[i], p1);
        dist2[i] = dist(positions[i], p2);
    }

    double min_sum = 1e9;
    for (int i = 0; i < N; ++i) {
        double r1 = dist1[i];
        double r2 = 0;
        for (int j = 0; j < N; ++j) {
            if (dist1[j] > r1) {
                r2 = max(r2, dist2[j]);
            }
        }
        min_sum = min(min_sum, r1 + r2);
    }

    for (int i = 0; i < N; ++i) {
        double r2 = dist2[i];
        double r1 = 0;
        for (int j = 0; j < N; ++j) {
            if (dist2[j] > r2) {
                r1 = max(r1, dist1[j]);
            }
        }
        min_sum = min(min_sum, r1 + r2);
    }

    cout << static_cast<int>(ceil(min_sum)) << endl;
    return 0;
}