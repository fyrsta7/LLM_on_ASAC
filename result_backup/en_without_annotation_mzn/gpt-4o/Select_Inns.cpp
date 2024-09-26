#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Hotel {
    int city;
    int price;
};

int main() {
    int n, k, p;
    cin >> n >> k >> p;

    vector<Hotel> hotels(n);
    for (int i = 0; i < n; ++i) {
        cin >> hotels[i].city >> hotels[i].price;
    }

    vector<pair<int, int>> plans;
    int num = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (hotels[i].city == hotels[j].city) {
                bool price_in_range = false;
                for (int t = i; t <= j; ++t) {
                    if (hotels[t].price <= p) {
                        price_in_range = true;
                        break;
                    }
                }
                if (price_in_range) {
                    plans.push_back({i + 1, j + 1});
                    ++num;
                }
            }
        }
    }

    cout << num << endl;
    return 0;
}