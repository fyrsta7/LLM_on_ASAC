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

    int best_A_s = 0, best_B_s = 0;
    int min_diff = INT_MAX;

    for (int A_s = 1; A_s <= L; ++A_s) {
        for (int B_s = 1; B_s <= L; ++B_s) {
            if (A_s * B >= A * B_s && gcd(A_s, B_s) == 1) {
                int diff = A_s * B - A * B_s;
                if (diff < min_diff) {
                    min_diff = diff;
                    best_A_s = A_s;
                    best_B_s = B_s;
                }
            }
        }
    }

    cout << best_A_s << " " << best_B_s << endl;

    return 0;
}