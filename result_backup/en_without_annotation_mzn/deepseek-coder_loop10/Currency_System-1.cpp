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
    vector<vector<int>> express_a(T), express_b(T);

    for (int i = 0; i < T; ++i) {
        express_a[i].resize(max_n[i] + 1, 0);
        express_b[i].resize(max_n[i] + 1, 0);
        for (int j = begin_n[i]; j < begin_n[i] + n[i]; ++j) {
            express_a[i][a[j]] = 1;
            express_b[i][b[j]] = 1;
        }
    }

    for (int i = 0; i < T; ++i) {
        for (int j = 1; j <= max_n[i]; ++j) {
            if (express_a[i][j]) {
                for (int k = begin_n[i]; k < begin_n[i] + n[i]; ++k) {
                    if (j + a[k] <= max_n[i]) express_a[i][j + a[k]] = 1;
                }
            }
            if (express_b[i][j]) {
                for (int k = begin_n[i]; k < begin_n[i] + n[i]; ++k) {
                    if (j + b[k] <= max_n[i]) express_b[i][j + b[k]] = 1;
                }
            }
        }
    }

    for (int i = 0; i < T; ++i) {
        if (express_a[i] != express_b[i]) {
            cout << "Error: Expressions do not match!" << endl;
            return 1;
        }
    }

    vector<int> m(T);
    for (int i = 0; i < T; ++i) {
        m[i] = n[i];
    }

    int total_m = accumulate(m.begin(), m.end(), 0);
    cout << total_m << endl;

    return 0;
}
