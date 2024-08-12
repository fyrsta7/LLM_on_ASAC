#include <iostream>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        swap(a %= b, b);
    }
    return a;
}

int main() {
    long long A, B, L;
    cin >> A >> B >> L;

    long long best_a = A, best_b = B;

    for (long long b_prime = 1; b_prime <= L; ++b_prime) {
        long long a_prime = (A * b_prime + B - 1) / B; // ceil(A * b_prime / B)
        if (a_prime <= L && gcd(a_prime, b_prime) == 1) {
            if (a_prime * B - b_prime * A < best_a * B - best_b * A) {
                best_a = a_prime;
                best_b = b_prime;
            }
        }
    }
    
    cout << best_a << ' ' << best_b << endl;
    return 0;
}