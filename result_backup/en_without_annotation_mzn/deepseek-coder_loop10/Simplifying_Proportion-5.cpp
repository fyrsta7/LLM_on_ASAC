#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int A, B, L;
    cin >> A >> B >> L;

    int A_s = 0, B_s = 0;
    int min_diff = INT_MAX;

    for (int i = 1; i <= L; ++i) {
        for (int j = 1; j <= L; ++j) {
            if (gcd(i, j) == 1 && (i * B >= j * A)) {
                int diff = i * B - j * A;
                if (diff < min_diff) {
                    min_diff = diff;
                    A_s = i;
                    B_s = j;
                }
            }
        }
    }

    cout << A_s << " " << B_s << endl;
    return 0;
}