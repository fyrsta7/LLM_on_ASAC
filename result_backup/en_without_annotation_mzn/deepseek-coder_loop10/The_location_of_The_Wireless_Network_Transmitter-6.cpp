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

int calculate_num(const Point& center) {
    int num = 0;
    for (int i = 0; i < n; ++i) {
        if (cover_spot(public_loc[i], center)) {
            num += public_num[i];
        }
    }
    return num;
}

int main() {
    cin >> d >> n;
    public_loc.resize(n);
    public_num.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> public_loc[i].x >> public_loc[i].y >> public_num[i];
    }

    const int max_plans = 100;
    vector<Point> ans;
    int best_score = 0;

    for (int x = 0; x <= 128; ++x) {
        for (int y = 0; y <= 128; ++y) {
            Point center = {x, y};
            int num = calculate_num(center);
            int score = max_plans * num + ans.size() + 1;
            if (score > best_score) {
                best_score = score;
                ans.clear();
                ans.push_back(center);
            } else if (score == best_score) {
                ans.push_back(center);
            }
            if (ans.size() >= max_plans) break;
        }
        if (ans.size() >= max_plans) break;
    }

    int plans = ans.size();
    int num = calculate_num(ans[0]);
    cout << plans << " " << num << endl;

    return 0;
}