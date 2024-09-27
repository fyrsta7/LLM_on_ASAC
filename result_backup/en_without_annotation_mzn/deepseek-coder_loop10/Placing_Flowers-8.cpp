#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    vector<int> B(n, 0);
    int remaining = m;

    for (int i = 0; i < n; ++i) {
        if (remaining == 0) break;
        int take = min(A[i], remaining);
        B[i] = take;
        remaining -= take;
    }

    for (int i = 0; i < n; ++i) {
        cout << B[i] << " ";
    }
    cout << endl;

    return 0;
}