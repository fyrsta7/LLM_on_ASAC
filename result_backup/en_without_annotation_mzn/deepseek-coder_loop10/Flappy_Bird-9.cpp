#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> X(n), Y(n);
    for (int i = 0; i < n; ++i) cin >> X[i];
    for (int i = 0; i < n; ++i) cin >> Y[i];
    vector<vector<int>> tube(k, vector<int>(3));
    for (int i = 0; i < k; ++i) cin >> tube[i][0] >> tube[i][1] >> tube[i][2];

    vector<int> bird(n + 1, 1);
    vector<int> tap(n + 1, 0);
    vector<int> d(n, 0);

    auto move = [](int x, int y, int t) {
        return t == 0 ? -y : x * t;
    };

    int pass_tube = 0;
    vector<vector<int>> sorted_tube = tube;
    sort(sorted_tube.begin(), sorted_tube.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });

    for (int i = 0; i < n; ++i) {
        d[i] = move(X[i], Y[i], tap[i + 1]);
        bird[i + 1] = bird[i] + d[i] >= m ? m : bird[i] + d[i];
    }

    for (int i = 0; i < k; ++i) {
        if (bird[sorted_tube[i][0]] > sorted_tube[i][1] && bird[sorted_tube[i][0]] < sorted_tube[i][2]) {
            pass_tube++;
        }
    }

    int score = accumulate(tap.begin(), tap.end(), 0) - pass_tube * m;
    if (pass_tube == k) {
        cout << "1\n" << score << endl;
    } else {
        cout << "0\n" << pass_tube << endl;
    }

    return 0;
}