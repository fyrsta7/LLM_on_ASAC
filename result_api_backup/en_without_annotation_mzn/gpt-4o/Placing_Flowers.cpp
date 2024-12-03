#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool solve(const vector<int>& A, vector<int>& B, int m, int i, int n) {
    if (i == n) return accumulate(B.begin(), B.end(), 0) == m;
    for (int val = min(A[i], m); val >= 0; --val) {
        B[i] = val;
        if (solve(A, B, m - val, i + 1, n)) return true;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(n, 0);
    for (int i = 0; i < n; ++i) cin >> A[i];
    if (solve(A, B, m, 0, n)) {
        for (int i = 0; i < n; ++i) cout << B[i] << " ";
    } else {
        cout << "No solution";
    }
    return 0;
}