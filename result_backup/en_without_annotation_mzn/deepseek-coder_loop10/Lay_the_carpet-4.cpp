#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> carpets(n, vector<int>(4));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> carpets[i][j];
        }
    }
    int x, y;
    cin >> x >> y;

    int ans = -1;
    for (int i = 0; i < n; ++i) {
        if (x >= carpets[i][0] && x <= carpets[i][0] + carpets[i][2] &&
            y >= carpets[i][1] && y <= carpets[i][1] + carpets[i][3]) {
            ans = max(ans, i + 1);
        }
    }

    cout << ans << endl;
    return 0;
}