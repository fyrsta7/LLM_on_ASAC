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
        vector<int> before = position[step - 1];
        vector<int> after(n);
        vector<int> shift_list(n);

        for (int i = 0; i < n; ++i) {
            shift_list[i] = i + 1;
        }

        do {
            bool valid = true;
            for (int i = 0; i < n; ++i) {
                after[i] = before[shift_list[i] - 1];
                if (i > 0 && after[i] == after[i - 1]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                for (int i = 0; i < n; ++i) {
                    int pos = after[i];
                    int pre = after[precede(i) - 1];
                    int fol = after[follow(i) - 1];
                    if ((pre != like[pos - 1][0] || fol != like[pos - 1][1]) &&
                        (pre != like[pos - 1][1] || fol != like[pos - 1][0])) {
                        valid = false;
                        break;
                    }
                }
            }

            if (valid) {
                position[step] = after;
                shift[step - 1] = shift_list;
                M[step - 1] = n;
                ++steps;
                break;
            }
        } while (next_permutation(shift_list.begin(), shift_list.end()));
    }

    int ans = 0;
    for (int i = 0; i < steps; ++i) {
        ans += M[i];
    }

    cout << ans << endl;
    return 0;
}
