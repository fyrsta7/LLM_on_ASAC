#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long n;
    cin >> n;
    
    long long larger_prime = 0;
    
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            long long other_prime = n / i;
            if (i != other_prime) {
                larger_prime = max(i, other_prime);
            }
            break; // No need to check further, since n is the product of two primes
        }
    }

    cout << larger_prime << endl;
    return 0;
}