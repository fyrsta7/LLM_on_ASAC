#include <iostream>
#include <cmath>
using namespace std;

int gcd(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

int main() {
    int A, B, L;
    cin >> A >> B >> L;

    double min_diff = 1e9;
    int best_Ap = 0, best_Bp = 0;

    for (int Ap = 1; Ap <= L; ++Ap) {
        for (int Bp = 1; Bp <= L; ++Bp) {
            if (gcd(Ap, Bp) == 1) {
                double original_ratio = static_cast<double>(A) / B;
                double new_ratio = static_cast<double>(Ap) / Bp;
                if (new_ratio >= original_ratio) {
                    double diff = new_ratio - original_ratio;
                    if (diff < min_diff) {
                        min_diff = diff;
                        best_Ap = Ap;
                        best_Bp = Bp;
                    }
                }
            }
        }
    }

    cout << best_Ap << " " << best_Bp << endl;
    return 0;
}