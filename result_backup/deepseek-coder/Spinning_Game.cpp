#include <iostream>
using namespace std;

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long n, m, k, x;
    cin >> n >> m >> k >> x;
    long long shift = mod_pow(10, k, n);
    long long final_position = (x + m * shift) % n;
    cout << final_position << endl;
    return 0;
}
