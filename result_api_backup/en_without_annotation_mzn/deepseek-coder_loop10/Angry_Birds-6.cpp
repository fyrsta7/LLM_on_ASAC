#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

struct Point {
    float x, y;
};

bool is_line_valid(const vector<Point>& points, float a, float b) {
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
    vector<Point> points(sum_n);
    for (int i = 0; i < sum_n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<int> split_n(T);
    for (int i = 1; i < T; ++i) {
        split_n[i] = split_n[i - 1] + n[i - 1];
    }

    vector<int> answer(T, 0);

    for (int t = 0; t < T; ++t) {
        for (int j = split_n[t]; j < split_n[t] + n[t]; ++j) {
            bool found = false;
            for (float a = -10.0; a < 0.0 && !found; a += 0.1) {
                for (float b = -10.0; b <= 10.0 && !found; b += 0.1) {
                    if (is_line_valid(vector<Point>(points.begin() + split_n[t], points.begin() + split_n[t] + n[t]), a, b)) {
                        found = true;
                        ++answer[t];
                    }
                }
            }
        }
    }

    for (int i = 0; i < T; ++i) {
        cout << answer[i] << " ";
    }
    cout << endl;

    return 0;
}
