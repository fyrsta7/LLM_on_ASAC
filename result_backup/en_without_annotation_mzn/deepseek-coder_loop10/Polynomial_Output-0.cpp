#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

string formatCoefficient(int coeff, int power, bool isFirst) {
    string result;
    if (coeff == 0) return result;
    if (coeff < 0) result += "-";
    else if (!isFirst) result += "+";
    if (abs(coeff) != 1) result += to_string(abs(coeff));
    if (power > 0) {
        result += "x";
        if (power > 1) result += "^" + to_string(power);
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> coefficient(n + 2);
    for (int i = 1; i <= n + 1; ++i) {
        cin >> coefficient[i];
    }

    bool isFirst = true;
    for (int i = 1; i <= n; ++i) {
        if (coefficient[i] != 0) {
            cout << formatCoefficient(coefficient[i], n - i + 1, isFirst);
            isFirst = false;
        }
    }

    if (coefficient[n + 1] != 0) {
        cout << (coefficient[n + 1] > 0 ? "+" : "-") << abs(coefficient[n + 1]);
    }

    cout << endl;
    return 0;
}
