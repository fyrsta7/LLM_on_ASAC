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
            int prev = precede(i + 1);
            int next = follow(i + 1);
            if (position[step - 1][i] == like[position[step - 1][prev - 1] - 1][0] ||
                position[step - 1][i] == like[position[step - 1][next - 1] - 1][0]) {
                new_position[i] = like[position[step - 1][i] - 1][1];
            } else {
                new_position[i] = like[position[step - 1][i] - 1][0];
            }
        }

        vector<int> shift_list(n);
        for (int i = 0; i < n; ++i) {
            shift_list[i] = i + 1;
        }
        sort(shift_list.begin(), shift_list.end(), [&](int a, int b) {
            return new_position[a - 1] < new_position[b - 1];
        });

        for (int i = 0; i < n; ++i) {
            position[step][i] = new_position[i];
            shift[step - 1][i] = shift_list[i];
        }

        M[step - 1] = 1;
        for (int i = 1; i < n; ++i) {
            if (position[step - 1][shift_list[i] - 1] != position[step][shift_list[i - 1] - 1]) {
                M[step - 1]++;
            }
        }
        steps++;
    }

    int ans = 0;
    for (int i = 0; i < steps; ++i) {
        ans += M[i];
    }

    cout << ans << endl;
    return 0;
}
