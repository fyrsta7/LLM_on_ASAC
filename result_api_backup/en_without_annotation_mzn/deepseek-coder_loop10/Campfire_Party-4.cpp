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
        vector<int> current_position = position[step - 1];
        vector<int> next_position(n);
        vector<int> shift_list(n);

        for (int i = 0; i < n; ++i) {
            int p = current_position[i];
            int left = precede(p);
            int right = follow(p);
            if (like[p - 1][0] == left && like[p - 1][1] == right) {
                next_position[i] = p;
            } else if (like[p - 1][0] == right && like[p - 1][1] == left) {
                next_position[i] = p;
            } else {
                next_position[i] = p;
            }
        }

        for (int i = 0; i < n; ++i) {
            shift_list[i] = i + 1;
        }

        M[step - 1] = 1;
        for (int i = 0; i < n; ++i) {
            shift[step - 1][i] = shift_list[i];
        }

        position[step] = next_position;
        steps++;
    }

    int ans = 0;
    for (int i = 0; i < steps; ++i) {
        ans += M[i];
    }

    cout << ans << endl;
    return 0;
}
