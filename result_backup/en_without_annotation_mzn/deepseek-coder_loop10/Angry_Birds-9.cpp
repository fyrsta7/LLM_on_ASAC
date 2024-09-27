#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

struct Point {
    float x, y;
};

bool isLineValid(const vector<Point>& points, float a, float b) {
    for (const auto& p : points) {
        if (abs(a * p.x * p.x + b * p.x - p.y) > 1e-6) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    vector<int> n(T);
    for (int i = 0; i < T; ++i) {
        cin >> n[i];
    }

    int sum_n = accumulate(n.begin(), n.end(), 0);
    vector<float> x(sum_n), y(sum_n);
    for (int i = 0; i < sum_n; ++i) {
        cin >> x[i] >> y[i];
    }

    vector<int> split_n(T);
    for (int i = 1; i < T; ++i) {
        split_n[i] = split_n[i - 1] + n[i - 1];
    }

    vector<int> answer(T, 0);
    for (int t = 0; t < T; ++t) {
        vector<Point> points(n[t]);
        for (int i = 0; i < n[t]; ++i) {
            points[i] = {x[split_n[t] + i], y[split_n[t] + i]};
        }

        for (float a = -10.0; a < 0.0; a += 0.1) {
            for (float b = -10.0; b <= 10.0; b += 0.1) {
                if (isLineValid(points, a, b)) {
                    answer[t]++;
                }
            }
        }
    }

    for (int ans : answer) {
        cout << ans << " ";
    }
    cout << endl;

    return 0;
}
