#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    int x, y;
};

inline int dist2(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int main() {
    int x1, y1, x2, y2, N;
    cin >> x1 >> y1 >> x2 >> y2 >> N;
    vector<Point> positions(N);
    for (int i = 0; i < N; ++i) {
        cin >> positions[i].x >> positions[i].y;
    }

    int min_sum = numeric_limits<int>::max();
    for (int r1 = 0; r1 < numeric_limits<int>::max(); ++r1) {
        int r1s = r1 * r1;
        bool all_covered = true;

        for (const auto& p : positions) {
            if (dist2({x1, y1}, p) > r1s && dist2({x2, y2}, p) == 0) {
                all_covered = false;
                break;
            }
        }

        if (all_covered) {
            int r2_max = 0;
            for (const auto& p : positions) {
                if (dist2({x1, y1}, p) <= r1s) continue;
                r2_max = max(r2_max, dist2({x2, y2}, p));
            }
            min_sum = min(min_sum, r1s + r2_max);
        }
    }

    cout << min_sum << endl;
    return 0;
}