#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
};

int d, n;
vector<Point> public_loc;
vector<int> public_num;

bool cover_spot(const Point& loc, const Point& center) {
    return max(abs(loc.x - center.x), abs(loc.y - center.y)) <= d;
}

int main() {
    cin >> d >> n;
    public_loc.resize(n);
    public_num.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> public_loc[i].x >> public_loc[i].y >> public_num[i];
    }

    int max_plans = 100;
    vector<Point> ans;
    int max_score = 0;
    int best_plans = 0;
    int best_num = 0;

    for (int x = 0; x <= 128; ++x) {
        for (int y = 0; y <= 128; ++y) {
            Point center = {x, y};
            int num = 0;
            for (int i = 0; i < n; ++i) {
                if (cover_spot(public_loc[i], center)) {
                    num += public_num[i];
                }
            }
            int score = max_plans * num + ans.size() + 1;
            if (score > max_score) {
                max_score = score;
                best_plans = ans.size() + 1;
                best_num = num;
            }
            if (ans.size() < max_plans) {
                ans.push_back(center);
            }
        }
    }

    cout << best_plans << " " << best_num << endl;
    return 0;
}