#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

double dist2(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    int x1, y1, x2, y2, N;
    cin >> x1 >> y1 >> x2 >> y2 >> N;
    vector<Point> positions(N);
    for (int i = 0; i < N; ++i) {
        cin >> positions[i].x >> positions[i].y;
    }

    vector<double> dist1(N), dist2(N);
    for (int i = 0; i < N; ++i) {
        dist1[i] = dist2(positions[i].x, positions[i].y, x1, y1);
        dist2[i] = dist2(positions[i].x, positions[i].y, x2, y2);
    }

    double r1s = 0, r2s = 0;
    for (int i = 0; i < N; ++i) {
        if (dist1[i] > r1s && dist2[i] > r2s) {
            if (dist1[i] <= dist2[i]) {
                r1s = dist1[i];
            } else {
                r2s = dist2[i];
            }
        }
    }

    cout << static_cast<int>(ceil(sqrt(r1s)) + ceil(sqrt(r2s))) << endl;
    return 0;
}