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
    int best_score = 0;
    int best_plans = 0;
    int best_num = 0;

    for (int x = 0; x <= 128; ++x) {
        for (int y = 0; y <= 128; ++y) {
            vector<pair<int, int>> centers;
            centers.emplace_back(x, y);
            for (int dx = -d; dx <= d; ++dx) {
                for (int dy = -d; dy <= d; ++dy) {
                    if (dx != 0 || dy != 0) {
                        centers.emplace_back(x + dx, y + dy);
                    }
                }
            }

            for (const auto& center : centers) {
                int num = 0;
                for (int i = 0; i < n; ++i) {
                    if (cover_spot(public_loc[i], center)) {
                        num += public_num[i];
                    }
                }

                int plans = 1;
                int score = max_plans * num + plans;
                if (score > best_score) {
                    best_score = score;
                    best_plans = plans;
                    best_num = num;
                }
            }
        }
    }

    cout << best_plans << " " << best_num << endl;
    return 0;
}