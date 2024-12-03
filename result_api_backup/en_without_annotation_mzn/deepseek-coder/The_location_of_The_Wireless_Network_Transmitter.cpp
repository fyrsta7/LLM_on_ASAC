#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int d, n;
vector<pair<int, int>> public_loc;
vector<int> public_num;

bool cover_spot(const pair<int, int>& loc, const pair<int, int>& center) {
    return max(abs(loc.first - center.first), abs(loc.second - center.second)) <= d;
}

int main() {
    cin >> d >> n;
    public_loc.resize(n);
    public_num.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> public_loc[i].first >> public_loc[i].second >> public_num[i];
    }

    int max_plans = 100;
    vector<pair<int, int>> ans;
    int best_plans = 0, best_num = 0;

    for (int x = 0; x <= 128; ++x) {
        for (int y = 0; y <= 128; ++y) {
            int num = 0;
            for (int i = 0; i < n; ++i) {
                if (cover_spot(public_loc[i], {x, y})) {
                    num += public_num[i];
                }
            }
            ans.emplace_back(x, y);
            if (ans.size() > max_plans) {
                sort(ans.begin(), ans.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
                    int num_a = 0, num_b = 0;
                    for (int i = 0; i < n; ++i) {
                        if (cover_spot(public_loc[i], a)) num_a += public_num[i];
                        if (cover_spot(public_loc[i], b)) num_b += public_num[i];
                    }
                    return num_a > num_b;
                });
                ans.pop_back();
            }
        }
    }

    for (const auto& center : ans) {
        int num = 0;
        for (int i = 0; i < n; ++i) {
            if (cover_spot(public_loc[i], center)) {
                num += public_num[i];
            }
        }
        if (num > best_num) {
            best_num = num;
            best_plans = ans.size();
        }
    }

    cout << best_plans << " " << best_num << endl;
    return 0;
}