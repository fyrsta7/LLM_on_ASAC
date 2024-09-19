#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int A, B, L;
    cin >> A >> B >> L;

    double original_ratio = (double)A / B;
    double min_diff = 1e9;
    int best_A = 1, best_B = 1;

    for (int A_prime = 1; A_prime <= L; ++A_prime) {
        for (int B_prime = 1; B_prime <= L; ++B_prime) {
            if (gcd(A_prime, B_prime) == 1) {
                double new_ratio = (double)A_prime / B_prime;
                double diff = new_ratio - original_ratio;
                if (diff >= 0 && diff < min_diff) {
                    min_diff = diff;
                    best_A = A_prime;
                    best_B = B_prime;
                }
            }
        }
    }

    cout << best_A << " " << best_B << endl;
    return 0;
}
