#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

int dist2(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    int x1, y1, x2, y2, N;
    cin >> x1 >> y1 >> x2 >> y2 >> N;
    vector<Point> positions(N);
    for (int i = 0; i < N; ++i) {
        cin >> positions[i].x >> positions[i].y;
    }

    vector<int> dist1(N), dist2(N);
    for (int i = 0; i < N; ++i) {
        dist1[i] = dist2(positions[i].x, positions[i].y, x1, y1);
        dist2[i] = dist2(positions[i].x, positions[i].y, x2, y2);
    }

    int r1s = 0, r2s = 0;
    for (int i = 0; i < N; ++i) {
        r1s = max(r1s, dist1[i]);
        r2s = max(r2s, dist2[i]);
    }

    int min_sum = r1s + r2s;
    for (int i = 0; i < N; ++i) {
        r1s = dist1[i];
        r2s = 0;
        for (int j = 0; j < N; ++j) {
            if (dist1[j] > r1s) {
                r2s = max(r2s, dist2[j]);
            }
        }
        min_sum = min(min_sum, r1s + r2s);
    }

    cout << min_sum << endl;
    return 0;
}