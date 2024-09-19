#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int coeffs[n+1];

    for (int i = 0; i <= n; ++i) {
        cin >> coeffs[i];
    }

    bool first = true;
    for (int i = 0; i <= n; ++i) {
        int coeff = coeffs[i];
        if (coeff != 0) {
            if (!first) {
                if (coeff > 0) {
                    cout << "+";
                } else {
                    cout << "-";
                    coeff = -coeff;
                }
            } else {
                if (coeff < 0) {
                    cout << "-";
                    coeff = -coeff;
                }
                first = false;
            }
            if (coeff != 1 || i == n) {
                cout << coeff;
            }
            if (i < n) {
                cout << "x";
                if (n - i > 1) {
                    cout << "^" << (n - i);
                }
            }
        }
    }
    return 0;
}