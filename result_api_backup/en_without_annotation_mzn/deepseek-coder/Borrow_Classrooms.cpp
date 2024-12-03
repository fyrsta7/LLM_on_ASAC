#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> r(n);
    for (int i = 0; i < n; ++i) cin >> r[i];
    vector<int> d(m), s(m), t(m);
    for (int i = 0; i < m; ++i) cin >> d[i] >> s[i] >> t[i];

    vector<int> state = r;
    int num = 0;

    for (int i = 0; i < m; ++i) {
        bool valid = true;
        for (int j = s[i] - 1; j < t[i]; ++j) {
            state[j] -= d[i];
            if (state[j] < 0) valid = false;
        }
        if (!valid) {
            cout << "-1\n" << i + 1 << endl;
            return 0;
        }
        num = i + 1;
    }

    cout << "0" << endl;
    return 0;
}
