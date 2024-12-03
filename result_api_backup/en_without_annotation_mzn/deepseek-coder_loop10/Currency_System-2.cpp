#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int T;
    cin >> T;
    vector<int> n(T);
    for (int i = 0; i < T; ++i) {
        cin >> n[i];
    }

    int sum_n = accumulate(n.begin(), n.end(), 0);
    vector<int> a(sum_n);
    for (int i = 0; i < sum_n; ++i) {
        cin >> a[i];
    }

    vector<int> begin_n(T);
    for (int i = 1; i < T; ++i) {
        begin_n[i] = begin_n[i - 1] + n[i - 1];
    }

    vector<int> max_n(T);
    for (int i = 0; i < T; ++i) {
        max_n[i] = accumulate(a.begin() + begin_n[i], a.begin() + begin_n[i] + n[i], 0);
    }

    int bound = *max_element(max_n.begin(), max_n.end());

    vector<int> b(sum_n, 1);
    vector<int> m(T);

    for (int i = 0; i < T; ++i) {
        vector<int> sub_a(a.begin() + begin_n[i], a.begin() + begin_n[i] + n[i]);
        vector<int> sub_b(b.begin() + begin_n[i], b.begin() + begin_n[i] + n[i]);

        vector<bool> express_a(max_n[i] + 1, false);
        vector<bool> express_b(max_n[i] + 1, false);

        for (int j = 0; j < n[i]; ++j) {
            express_a[sub_a[j]] = true;
            express_b[sub_b[j]] = true;
        }

        for (int j = 1; j <= max_n[i]; ++j) {
            if (express_a[j]) {
                for (int k = 0; k < n[i]; ++k) {
                    if (j + sub_a[k] <= max_n[i]) {
                        express_a[j + sub_a[k]] = true;
                    }
                }
            }
            if (express_b[j]) {
                for (int k = 0; k < n[i]; ++k) {
                    if (j + sub_b[k] <= max_n[i]) {
                        express_b[j + sub_b[k]] = true;
                    }
                }
            }
        }

        for (int j = 1; j <= max_n[i]; ++j) {
            if (express_a[j] != express_b[j]) {
                b[begin_n[i] + (j - 1) % n[i]] = j;
                express_b[j] = true;
            }
        }

        m[i] = set<int>(sub_b.begin(), sub_b.end()).size();
    }

    int total_m = accumulate(m.begin(), m.end(), 0);
    cout << total_m << endl;

    return 0;
}
