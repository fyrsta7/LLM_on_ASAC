#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int m = 1;  // Initialize m to the smallest possible value, 1 which is invalid, hence we start checking from 2
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) {
            m = i;
        }
    }

    cout << m << endl;
    return 0;
}