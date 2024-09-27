#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
    while (b) {
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
    int max_T = 10000;

    vector<int> time(N, max_T);

    for (int i = 0; i < N; ++i) {
        for (int t = 1; t <= max_T; ++t) {
            if ((int)pow(S[i], t) % M == 0) {
                time[i] = t;
                break;
            }
        }
    }

    int ans = *min_element(time.begin(), time.end());

    if (ans == max_T) {
        cout << "-1" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
