#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

string polynomialToString(int n, const vector<int>& coefficient) {
    string result;
    for (int i = 0; i <= n; ++i) {
        if (coefficient[i] == 0) continue;

        if (!result.empty()) {
            result += (coefficient[i] > 0) ? "+" : "-";
        } else if (coefficient[i] < 0) {
            result += "-";
        }

        if (abs(coefficient[i]) != 1 || (n - i == 0)) {
            result += to_string(abs(coefficient[i]));
        }

        if (n - i > 0) {
            result += "x";
            if (n - i > 1) {
                result += "^" + to_string(n - i);
            }
        }
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> coefficient(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> coefficient[i];
    }
    cout << polynomialToString(n, coefficient) << endl;
    return 0;
}