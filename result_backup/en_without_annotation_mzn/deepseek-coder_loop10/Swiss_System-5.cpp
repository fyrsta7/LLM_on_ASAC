#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, R, Q;
    cin >> N >> R >> Q;
    vector<int> s(2 * N);
    vector<int> w(2 * N);
    vector<int> p(2 * N);

    for (int i = 0; i < 2 * N; ++i) {
        cin >> s[i];
        p[i] = i + 1;
    }
    for (int i = 0; i < 2 * N; ++i) {
        cin >> w[i];
    }

    auto cmp = [&](int a, int b) {
        if (s[a - 1] == s[b - 1]) return a < b;
        return s[a - 1] > s[b - 1];
    };

    for (int r = 0; r <= R; ++r) {
        sort(p.begin(), p.end(), cmp);
        if (r == R) break;
        for (int j = 0; j < N; ++j) {
            int a = p[2 * j] - 1;
            int b = p[2 * j + 1] - 1;
            if (w[a] > w[b]) {
                s[a]++;
            } else {
                s[b]++;
            }
        }
    }

    cout << p[Q - 1] << endl;
    return 0;
}
