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

    auto express = [&](int t, const vector<int>& x, set<int>& express_x) {
        express_x.clear();
        for (int v : x) {
            express_x.insert(v);
        }
        bool changed;
        do {
            changed = false;
            for (int i : express_x) {
                for (int j : x) {
                    if (i + j <= max_n[t] && express_x.find(i + j) == express_x.end()) {
                        express_x.insert(i + j);
                        changed = true;
                    }
                }
            }
        } while (changed);
    };

    for (int i = 0; i < T; ++i) {
        express(i, vector<int>(a.begin() + begin_n[i], a.begin() + begin_n[i] + n[i]), express_a[i]);
    }

    vector<int> m(T);
    for (int i = 0; i < T; ++i) {
        express(i, vector<int>(b.begin() + begin_n[i], b.begin() + begin_n[i] + n[i]), express_b[i]);
        if (express_a[i] != express_b[i]) {
            m[i] = n[i];
        } else {
            m[i] = express_b[i].size();
        }
    }

    for (int i = 0; i < T; ++i) {
        cout << m[i] << " ";
    }
    cout << endl;

    return 0;
}
