#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    int N, m1, m2;
    cin >> N >> m1 >> m2;
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }

    int M = pow(m1, m2);
    int ans = 10000;

    for (int i = 0; i < N; ++i) {
        int t = 1;
        while (true) {
            if ((int)pow(S[i], t) % M == 0) {
                ans = min(ans, t);
                break;
            }
            ++t;
        }
    }

    if (ans == 10000) {
        cout << "-1" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
