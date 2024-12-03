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

    const int max_plans = 100;
    vector<Point> ans;
    int best_score = 0;
    int best_plans = 0;
    int best_num = 0;

    for (int x = 0; x <= 128; ++x) {
        for (int y = 0; y <= 128; ++y) {
            Point center = {x, y};
            int num = 0;
            for (int i = 0; i < n; ++i) {
                if (cover_spot(public_loc[i], center, d)) {
                    num += public_num[i];
                }
            }
            int score = max_plans * num + 1;
            if (score > best_score) {
                best_score = score;
                best_plans = 1;
                best_num = num;
                ans.clear();
                ans.push_back(center);
            } else if (score == best_score) {
                if (ans.size() < max_plans) {
                    ans.push_back(center);
                    best_plans = ans.size();
                }
            }
        }
    }

    cout << best_plans << " " << best_num << endl;
    return 0;
}
