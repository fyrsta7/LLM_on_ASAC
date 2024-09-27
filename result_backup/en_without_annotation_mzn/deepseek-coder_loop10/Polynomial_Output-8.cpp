#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> coefficient(n + 2);
    for (int i = 1; i <= n + 1; ++i) {
        cin >> coefficient[i];
    }

    for (int i = 1; i <= n; ++i) {
        if (coefficient[i] < 0) {
            cout << "-";
        } else if (coefficient[i] > 0 && i > 1) {
            cout << "+";
        }

        if (abs(coefficient[i]) != 1 && coefficient[i] != 0) {
            cout << abs(coefficient[i]);
        }

        if (coefficient[i] != 0) {
            cout << "x";
            if (n - i + 1 != 1) {
                cout << "^" << (n - i + 1);
            }
        }
    }

    if (coefficient[n + 1] != 0) {
        if (coefficient[n + 1] > 0) {
            cout << "+";
        } else {
            cout << "-";
        }
        cout << abs(coefficient[n + 1]);
    }

    return 0;
}
