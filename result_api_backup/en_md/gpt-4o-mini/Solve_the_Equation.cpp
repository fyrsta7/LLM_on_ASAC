#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long long evaluatePolynomial(const vector<long long>& coeffs, long long x) {
    long long result = 0;
    long long xPower = 1;
    for (long long coeff : coeffs) {
        result += coeff * xPower;
        xPower *= x;
    }
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> coeffs(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> coeffs[i];
    }

    vector<long long> solutions;
    for (int x = 1; x <= m; ++x) {
        if (evaluatePolynomial(coeffs, x) == 0) {
            solutions.push_back(x);
        }
    }

    cout << solutions.size() << endl;
    for (long long sol : solutions) {
        cout << sol << endl;
    }

    return 0;
}