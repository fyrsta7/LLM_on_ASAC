#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> coefficients(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> coefficients[i];
    }

    bool firstTerm = true;
    for (int i = 0; i <= n; ++i) {
        int coeff = coefficients[i];
        if (coeff == 0) continue;

        if (firstTerm) {
            if (coeff < 0) cout << "-";
            firstTerm = false;
        } else {
            cout << (coeff < 0 ? "-" : "+");
        }

        int absCoeff = abs(coeff);
        int degree = n - i;
        if (absCoeff != 1 || degree == 0) {
            cout << absCoeff;
        }
        if (degree > 0) {
            cout << "x";
            if (degree > 1) {
                cout << "^" << degree;
            }
        }
    }
    cout << endl;
    return 0;
}