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

    int A_s = A, B_s = B;
    int min_diff = A * B_s - A_s * B;

    for (int i = 1; i <= L; ++i) {
        for (int j = 1; j <= L; ++j) {
            if (i * B >= j * A && gcd(i, j) == 1) {
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