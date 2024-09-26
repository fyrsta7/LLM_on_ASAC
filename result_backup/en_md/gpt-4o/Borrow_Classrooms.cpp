#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> rooms(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> rooms[i];
    }

    for (int j = 1; j <= m; ++j) {
        int d, s, t;
        cin >> d >> s >> t;
        bool canComplete = true;
        
        for (int k = s; k <= t; ++k) {
            if (rooms[k] < d) {
                canComplete = false;
                break;
            }
        }

        if (canComplete) {
            for (int k = s; k <= t; ++k) {
                rooms[k] -= d;
            }
        } else {
            cout << -1 << endl;
            cout << j << endl;
            return 0;
        }
    }

    cout << 0 << endl;
    return 0;
}