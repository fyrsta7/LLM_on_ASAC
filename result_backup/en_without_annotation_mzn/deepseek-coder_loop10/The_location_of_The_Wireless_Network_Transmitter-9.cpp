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
    int best_num = 0, best_plans = 0;

    for (int x = 0; x <= 128; ++x) {
        for (int y = 0; y <= 128; ++y) {
            int num = 0;
            for (int i = 0; i < n; ++i) {
                if (cover_spot(public_loc[i], {x, y})) {
                    num += public_num[i];
                }
            }
            ans.push_back({x, y});
            if (ans.size() > max_plans) break;
            if (num > best_num) {
                best_num = num;
                best_plans = ans.size();
            }
        }
        if (ans.size() > max_plans) break;
    }

    cout << best_plans << " " << best_num << endl;
    return 0;
}