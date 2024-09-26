#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

bool express(int t, const vector<int>& x, set<int>& express_x, int max_n_t) {
    express_x.clear();
    for (int val : x) {
        if(val >= 1 && val <= max_n_t) {
            express_x.insert(val);
        }
    }
    bool added = true;
    while (added) {
        added = false;
        for (int i = 1; i <= max_n_t; ++i) {
            if (express_x.count(i)) continue;
            for (int v : x) {
                if (i - v >= 1 && express_x.count(i - v)) {
                    express_x.insert(i);
                    added = true;
                    break;
                }
                for (int ex : express_x) {
                    if (i == ex + v) {
                        express_x.insert(i);
                        added = true;
                        break;
                    }
                }
                if (added) break;
            }
        }
    }
    return true;
}

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
    vector<int> max_n(T);
    begin_n[0] = 0;
    for (int i = 1; i < T; ++i) {
        begin_n[i] = begin_n[i - 1] + n[i - 1];
    }

    for (int i = 0; i < T; ++i) {
        for (int j = begin_n[i]; j < begin_n[i] + n[i]; ++j) {
            max_n[i] = max(max_n[i], a[j]);
        }
    }

    int bound = *max_element(max_n.begin(), max_n.end());

    vector<int> b(sum_n, 1);
    vector< set<int> > express_a(T);
    vector< set<int> > express_b(T);

    for (int i = 0; i < T; ++i) {
        express(i, vector<int>(begin_n[i] + n[i] - begin_n[i], bound), express_a[i], max_n[i]);
        express(i, vector<int>(begin_n[i] + n[i] - begin_n[i], bound), express_b[i], max_n[i]);
    }

    vector<int> m(T);
    for (int i = 0; i < T; ++i) {
        m[i] = express_b[i].size();
    }

    // Output the result
    for (int i = 0; i < T; ++i) {
        cout << m[i] << " ";
    }
    cout << endl;

    return 0;
}