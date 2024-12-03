#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Order {
    int d, s, t;
};

bool canFulfill(const vector<int>& rooms, const vector<Order>& orders, int m) {
    vector<int> diff(rooms.size() + 1, 0);
    for (int i = 0; i < m; ++i) {
        diff[orders[i].s] += orders[i].d;
        diff[orders[i].t + 1] -= orders[i].d;
    }
    int current = 0;
    for (size_t i = 1; i < rooms.size(); ++i) {
        current += diff[i];
        if (current > rooms[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> rooms(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> rooms[i];
    }

    vector<Order> orders(m);
    for (int i = 0; i < m; ++i) {
        cin >> orders[i].d >> orders[i].s >> orders[i].t;
    }

    int left = 0, right = m;
    while (left < right) {
        int mid = (left + right) / 2;
        if (canFulfill(rooms, vector<Order>(orders.begin(), orders.begin() + mid + 1), mid + 1)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (left == m) {
        cout << 0 << endl;
    } else {
        cout << -1 << endl;
        cout << left + 1 << endl;
    }

    return 0;
}
