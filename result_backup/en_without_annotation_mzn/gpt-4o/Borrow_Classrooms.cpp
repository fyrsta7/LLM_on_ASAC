#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> r(n), d(m), s(m), t(m);
    for (int i = 0; i < n; ++i) cin >> r[i];
    for (int i = 0; i < m; ++i) cin >> d[i];
    for (int i = 0; i < m; ++i) cin >> s[i];
    for (int i = 0; i < m; ++i) cin >> t[i];
    
    vector<vector<int>> state(m + 1, vector<int>(n));
    state[0] = r;
    
    int num = 0;
    for (int i = 1; i <= m; ++i) {
        bool valid = true;
        for (int j = 0; j < n; ++j) {
            if (j + 1 >= s[i - 1] && j + 1 <= t[i - 1]) {
                state[i][j] = state[i - 1][j] - d[i - 1];
            } else {
                state[i][j] = state[i - 1][j];
            }
            if (state[i][j] < 0) valid = false;
        }
        if (!valid) {
            cout << "-1\n" << i << endl;
            return 0;
        }
        num = i;
    }
    cout << "0" << endl;
    return 0;
}
