#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

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
    vector<set<int>> express_a(T), express_b(T);

    for (int i = 0; i < T; ++i) {
        for (int j = begin_n[i]; j < begin_n[i] + n[i]; ++j) {
            express_a[i].insert(a[j]);
            express_b[i].insert(b[j]);
        }
    }

    auto express = [&](int t, const vector<int>& x, set<int>& express_x) {
        for (int i : x) {
            express_x.insert(i);
        }
        for (int i : express_x) {
            for (int j : x) {
                if (i + j <= max_n[t]) {
                    express_x.insert(i + j);
                }
            }
        }
    };

    for (int i = 0; i < T; ++i) {
        express(i, vector<int>(a.begin() + begin_n[i], a.begin() + begin_n[i] + n[i]), express_a[i]);
        express(i, vector<int>(b.begin() + begin_n[i], b.begin() + begin_n[i] + n[i]), express_b[i]);
    }

    for (int i = 0; i < T; ++i) {
        if (express_a[i] != express_b[i]) {
            cout << "Error: express_a and express_b do not match for t=" << i << endl;
            return 1;
        }
    }

    vector<int> m(T);
    for (int i = 0; i < T; ++i) {
        m[i] = express_b[i].size();
    }

    for (int i = 0; i < T; ++i) {
        cout << m[i] << " ";
    }
    cout << endl;

    return 0;
}
