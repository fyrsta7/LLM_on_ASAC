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

    vector<int> b(sum_n);
    for (int i = 0; i < T; ++i) {
        for (int j = begin_n[i]; j < begin_n[i] + n[i]; ++j) {
            b[j] = 1;
        }
    }

    vector<int> m(T);
    for (int i = 0; i < T; ++i) {
        m[i] = n[i];
    }

    cout << accumulate(m.begin(), m.end(), 0) << endl;

    return 0;
}
