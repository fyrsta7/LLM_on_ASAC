#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> S(n);
    vector<int> A(n);
    for (int i = 0; i < n; ++i) cin >> S[i];
    for (int i = 0; i < n; ++i) cin >> A[i];

    vector<vector<int>> choose(n, vector<int>(n, 0));
    vector<int> r(n);
    vector<int> c(n);

    for (int i = 0; i < n; ++i) {
        int max_cost = -1;
        int best_r = -1;
        for (int j = 0; j < n; ++j) {
            int cost = A[j] * (i + 1) + S[j] * 2;
            if (cost > max_cost) {
                max_cost = cost;
                best_r = j;
            }
        }
        r[i] = best_r + 1;
        c[i] = max_cost;
        choose[i][best_r] = 1;
    }

    int total_cost = 0;
    for (int i = 0; i < n; ++i) {
        total_cost += c[i];
    }

    cout << "[";
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << ", ";
        cout << c[i];
    }
    cout << "]" << endl;

    return 0;
}