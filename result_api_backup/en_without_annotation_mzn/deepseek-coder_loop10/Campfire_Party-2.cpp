#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> like(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        cin >> like[i][0] >> like[i][1];
    }

    vector<vector<int>> position(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        position[0][i] = i + 1;
    }

    auto precede = [n](int i) { return i > 1 ? i - 1 : n; };
    auto follow = [n](int i) { return i < n ? i + 1 : 1; };

    int steps = n;
    vector<int> M(steps - 1, 1);
    vector<vector<int>> shift(steps - 1, vector<int>(n));

    for (int i = 0; i < steps - 1; ++i) {
        shift[i] = position[i];
        rotate(shift[i].begin(), shift[i].begin() + 1, shift[i].end());
    }

    for (int i = 1; i < steps; ++i) {
        position[i] = shift[i - 1];
    }

    int ans = 0;
    for (int i = 0; i < steps - 1; ++i) {
        ans += M[i];
    }

    cout << ans << endl;
    return 0;
}
