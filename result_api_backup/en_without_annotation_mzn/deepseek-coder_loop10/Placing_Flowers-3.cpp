#include <iostream>
#include <vector>

using namespace std;

bool canDistribute(int n, int m, vector<int>& A) {
    int sumA = 0;
    for (int i = 0; i < n; ++i) {
        sumA += A[i];
    }
    return sumA >= m;
}

void distribute(int n, int m, vector<int>& A, vector<int>& B) {
    for (int i = 0; i < n; ++i) {
        B[i] = min(A[i], m / n);
        m -= B[i];
    }
    for (int i = 0; i < n && m > 0; ++i) {
        int extra = min(A[i] - B[i], m);
        B[i] += extra;
        m -= extra;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    if (!canDistribute(n, m, A)) {
        cout << "Impossible" << endl;
        return 0;
    }

    vector<int> B(n, 0);
    distribute(n, m, A, B);

    for (int i = 0; i < n; ++i) {
        cout << B[i] << " ";
    }
    cout << endl;

    return 0;
}