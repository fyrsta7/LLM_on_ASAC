#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

string kthGrayCode(int n, long long k) {
    long long gray = k ^ (k >> 1); // Convert to Gray code using the formula
    string result;
    for (int i = n - 1; i >= 0; i--) {
        result += (gray & (1LL << i)) ? '1' : '0'; // Build the binary string
    }
    return result;
}

int main() {
    int n;
    long long k;
    cin >> n >> k;
    cout << kthGrayCode(n, k) << endl;
    return 0;
}