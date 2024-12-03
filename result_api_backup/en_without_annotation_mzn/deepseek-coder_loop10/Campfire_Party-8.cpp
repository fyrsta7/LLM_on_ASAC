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

    int steps = 0;
    vector<int> M(n, 0);
    vector<vector<int>> shift(n, vector<int>(n));

    for (int step = 1; step < n; ++step) {
        vector<int> new_position(n);
        for (int i = 0; i < n; ++i) {
            new_position[i] = position[step - 1][shift[step - 1][i] - 1];
        }

        bool valid = true;
        for (int i = 0; i < n; ++i) {
            int p = new_position[i];
            int prev = new_position[precede(i + 1) - 1];
            int next = new_position[follow(i + 1) - 1];
            if (!(prev == like[p - 1][0] && next == like[p - 1][1]) &&
                !(prev == like[p - 1][1] && next == like[p - 1][0])) {
                valid = false;
                break;
            }
        }

        if (valid) {
            position[step] = new_position;
            M[step - 1] = *max_element(shift[step - 1].begin(), shift[step - 1].end());
            steps = step;
        } else {
            break;
        }
    }

    int ans = 0;
    for (int i = 0; i < steps; ++i) {
        ans += M[i];
    }

    cout << ans << endl;
    return 0;
}
