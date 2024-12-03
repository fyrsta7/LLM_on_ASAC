#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
};

bool cover_spot(const Point& loc, const Point& center, int d) {
    return max(abs(loc.x - center.x), abs(loc.y - center.y)) <= d;
}

int main() {
    int d, n;
    cin >> d >> n;
    vector<Point> public_loc(n);
    vector<int> public_num(n);
    for (int i = 0; i < n; ++i) {
        cin >> public_loc[i].x >> public_loc[i].y >> public_num[i];
    }

    int max_plans = 100;
    int best_score = 0;
    int best_plans = 0;
    int best_num = 0;

    for (int plans = 1; plans <= max_plans; ++plans) {
        vector<Point> ans(plans);
        for (int i = 0; i < plans; ++i) {
            ans[i] = {0, 0};
        }

        int num = 0;
        for (int t = 0; t < plans; ++t) {
            int max_covered = 0;
            Point best_center = {0, 0};
            for (int x = 0; x <= 128; ++x) {
                for (int y = 0; y <= 128; ++y) {
                    int covered = 0;
                    for (int i = 0; i < n; ++i) {
                        if (cover_spot(public_loc[i], {x, y}, d)) {
                            covered += public_num[i];
                        }
                    }
                    if (covered > max_covered) {
                        max_covered = covered;
                        best_center = {x, y};
                    }
                }
            }
            ans[t] = best_center;
            num += max_covered;
        }

        int score = max_plans * num + plans;
        if (score > best_score) {
            best_score = score;
            best_plans = plans;
            best_num = num;
        }
    }

    cout << best_plans << " " << best_num << endl;
    return 0;
}
