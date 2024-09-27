#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int N, m1, m2;
    cin >> N >> m1 >> m2;
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }

    int M = pow(m1, m2);
    int max_T = 10000;
    int ans = max_T;

    for (int i = 0; i < N; ++i) {
        int t = 1;
        int power = S[i];
        while (t <= max_T && power % M != 0) {
            power = (power * S[i]) % M;
            ++t;
        }
        if (t <= max_T) {
            ans = min(ans, t);
        }
    }

    if (ans == max_T) {
        cout << "-1" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}