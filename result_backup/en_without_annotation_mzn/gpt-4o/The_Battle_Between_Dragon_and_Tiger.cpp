#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

int main() {
    int n, m, p1, s1, s2;
    cin >> n;
    vector<int> num(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> num[i];
    }
    cin >> m >> p1 >> s1 >> s2;
    
    int best_p2 = 1;
    int min_diff = numeric_limits<int>::max();

    for (int p2 = 1; p2 <= n; ++p2) {
        int left = 0, right = 0;
        
        for (int i = 1; i < m; ++i) {
            left += num[i] * (m - i);
        }
        if (p1 < m) left += s1 * (m - p1);
        if (p2 < m) left += s2 * (m - p2);

        for (int i = m + 1; i <= n; ++i) {
            right += num[i] * (i - m);
        }
        if (p1 > m) right += s1 * (p1 - m);
        if (p2 > m) right += s2 * (p2 - m);
        
        int diff = abs(left - right);
        if (diff < min_diff) {
            min_diff = diff;
            best_p2 = p2;
        }
    }

    cout << "p2=" << best_p2 << endl;
    return 0;
}