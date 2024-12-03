#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> S(n), A(n);
    for (int i = 0; i < n; ++i) cin >> S[i];
    for (int i = 0; i < n; ++i) cin >> A[i];

    vector<vector<int>> choose(n, vector<int>(n, 0));
    vector<int> r(n), c(n);

    for (int i = 0; i < n; ++i) {
        int max_cost = -1;
        for (int j = 0; j < n; ++j) {
            int cost = A[j] * (i + 1) + S[j] * 2;
            if (cost > max_cost) {
                max_cost = cost;
                r[i] = j + 1;
                c[i] = cost;
            }
        }
        for (int j = 0; j <= i; ++j) {
            choose[i][r[i] - 1] = 1;
        }
    }

    int total_cost = 0;
    for (int i = 0; i < n; ++i) {
        total_cost += c[i];
    }

    cout << total_cost << endl;

    return 0;
}