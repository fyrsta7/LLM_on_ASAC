#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> coefficient(n+1);
    for (int i = 0; i <= n; ++i) {
        cin >> coefficient[i];
    }

    bool firstTerm = true;

    for (int i = 0; i < n; ++i) {
        int coeff = coefficient[i];
        
        if (coeff == 0) continue;

        if (firstTerm) {
            if (coeff < 0) cout << "-";
            firstTerm = false;
        } else {
            if (coeff > 0) cout << "+";
            else cout << "-";
        }

        int absCoeff = abs(coeff);
        if (absCoeff != 1) cout << absCoeff;
        
        if (n-i > 1) {
            cout << "x";
            if (n-i > 2) cout << "^" << (n-i-1);
        }
    }
    
    // Handle the constant term n+1
    int constantTerm = coefficient[n];
    if (constantTerm != 0) {
        cout << (constantTerm > 0 ? "+" : "-") << abs(constantTerm);
    }
    
    return 0;
}