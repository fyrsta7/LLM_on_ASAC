#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Location {
    int x, y, num;
};

int d, n;
vector<Location> publicLoc;
int max_plans = 100;

bool cover_spot(const Location &loc, const Location &center) {
    return max(abs(loc.x - center.x), abs(loc.y - center.y)) <= d;
}

int compute_score(vector<Location> &plans) {
    vector<int> covered(publicLoc.size(), 0);
    int total_num = 0;
    for (auto &center : plans) {
        for (size_t i = 0; i < publicLoc.size(); ++i) {
            if (cover_spot(publicLoc[i], center)) {
                covered[i] = 1;
            }
        }
    }
    for (size_t i = 0; i < publicLoc.size(); ++i) {
        total_num += covered[i] * publicLoc[i].num;
    }
    return max_plans * total_num + plans.size();
}

int main() {
    cin >> d >> n;
    publicLoc.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> publicLoc[i].x >> publicLoc[i].y >> publicLoc[i].num;
    }
    
    vector<Location> plans;
    int best_num = 0;
    vector<Location> best_plans;
    for (int i = 0; i < n && plans.size() < max_plans; ++i) {
        Location new_center = {publicLoc[i].x, publicLoc[i].y};
        plans.push_back(new_center);
        int score = compute_score(plans);
        if (score > best_num) {
            best_num = score;
            best_plans = plans;
        }
    }

    cout << best_plans.size() << " " << best_num / max_plans << endl;
    return 0;
}
