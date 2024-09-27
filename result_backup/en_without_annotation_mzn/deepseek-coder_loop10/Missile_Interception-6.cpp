#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
};

int dist2(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int main() {
    int x1, y1, x2, y2, N;
    cin >> x1 >> y1 >> x2 >> y2 >> N;
    vector<Point> positions(N);
    for (int i = 0; i < N; ++i) {
        cin >> positions[i].x >> positions[i].y;
    }

    int r1s = 0, r2s = 0;
    for (const auto& pos : positions) {
        int d1 = dist2({x1, y1}, pos);
        int d2 = dist2({x2, y2}, pos);
        if (d1 > r1s) r1s = d1;
        if (d2 > r2s) r2s = d2;
    }

    cout << r1s + r2s << endl;
    return 0;
}