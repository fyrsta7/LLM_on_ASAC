#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, R, Q;
    cin >> N >> R >> Q;
    vector<int> s(2 * N);
    vector<int> w(2 * N);
    for (int i = 0; i < 2 * N; ++i) {
        cin >> s[i];
    }
    for (int i = 0; i < 2 * N; ++i) {
        cin >> w[i];
    }

    vector<int> p(2 * N);
    for (int i = 0; i < 2 * N; ++i) {
        p[i] = i;
    }

    auto cmp = [&](int a, int b) {
        if (s[a] != s[b]) return s[a] > s[b];
        return a < b;
    };

    for (int r = 0; r <= R; ++r) {
        sort(p.begin(), p.end(), cmp);
        if (r == R) {
            cout << p[Q - 1] + 1 << endl;
            break;
        }
        for (int j = 0; j < N; ++j) {
            int a = p[2 * j];
            int b = p[2 * j + 1];
            if (w[a] > w[b]) {
                s[a]++;
            } else {
                s[b]++;
            }
        }
    }

    return 0;
}
