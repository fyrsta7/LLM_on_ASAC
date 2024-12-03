#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> rooms(n);
    for (int i = 0; i < n; ++i) {
        cin >> rooms[i];
    }

    for (int j = 1; j <= m; ++j) {
        long long d, s, t;
        cin >> d >> s >> t;
        bool canFulfill = true;

        for (int day = s - 1; day < t; ++day) {
            if (rooms[day] < d) {
                canFulfill = false;
                break;
            }
        }

        if (!canFulfill) {
            cout << -1 << endl;
            cout << j << endl;
            return 0;
        }

        for (int day = s - 1; day < t; ++day) {
            rooms[day] -= d;
        }
    }
    
    cout << 0 << endl;
    return 0;
}