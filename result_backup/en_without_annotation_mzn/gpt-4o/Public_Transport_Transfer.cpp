#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Trip {
    int ty, price, time;
};

int main() {
    int n;
    cin >> n;
    vector<Trip> trips(n);
    for (int i = 0; i < n; ++i) {
        cin >> trips[i].ty >> trips[i].price >> trips[i].time;
    }
    
    vector<int> take(n), total(n+1, 0), prev(n+1, -1);
    
    for (int i = 0; i < n; ++i) {
        int best = total[i];
        for (int j = 0; j < i; ++j) {
            if (trips[j].ty == 0 && trips[j].time + 45 >= trips[i].time && trips[j].price <= trips[i].price) {
                int new_total = total[j + 1] + trips[i].price;
                if (new_total > best) {
                    best = new_total;
                    prev[i + 1] = j;
                }
            }
        }
        total[i + 1] = best;
    }

    cout << *max_element(total.begin(), total.end()) << endl;
    return 0;
}