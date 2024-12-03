#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

int gcd(int x, int y) {
    while (y != 0) {
        int t = y;
        y = x % y;
        x = t;
    }
    return x;
}

int main() {
    int A, B, L;
    cin >> A >> B >> L;
    
    int best_A_s = 1, best_B_s = 1;
    int min_diff = numeric_limits<int>::max(); 

    for (int B_s = 1; B_s <= L; ++B_s) {
        for (int A_s = 1; A_s <= L; ++A_s) {
            if (A_s * B >= B_s * A && gcd(A_s, B_s) == 1) {
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