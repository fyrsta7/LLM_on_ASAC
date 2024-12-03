#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> coefficients(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> coefficients[i];
    }

    stringstream result;
    bool firstTerm = true;

    for (int i = 0; i <= n; ++i) {
        int index = n - i;
        int coeff = coefficients[i];
        
        if (coeff != 0) {
            if (!firstTerm) {
                if (coeff > 0) {
                    result << "+";
                } else {
                    result << "-";
                }
            } else {
                if (coeff < 0) {
                    result << "-";
                }
                firstTerm = false;
            }

            int absCoeff = abs(coeff);
            if (index > 1) {
                if (absCoeff != 1) {
                    result << absCoeff;
                }
                result << "x^" << index;
            } else if (index == 1) {
                if (absCoeff != 1) {
                    result << absCoeff;
                }
                result << "x";
            } else {
                result << absCoeff;
            }
        }
    }

    cout << result.str();
    return 0;
}