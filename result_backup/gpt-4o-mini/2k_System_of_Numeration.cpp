#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long countR(int k, int w) {
    int m = 1 << k; // 2^k
    int maxDigits = w / k; // maximum number of segments
    vector<long long> dp(maxDigits + 1, 0);

    // Calculate possible numbers with 2 digits, 3 digits, ..., until maxDigits
    for (int digits = 2; digits <= maxDigits; digits++) {
        long long count = 0;
        for (int highestDigit = 1; highestDigit < m; highestDigit++) {
            int digitsLeft = digits - 1;
            int availableDigits = highestDigit; // digits from 1 to highestDigit-1
            count += (availableDigits * (availableDigits - 1)) / 2; // combination of choosing 2 from available
            for (int currentDigit = highestDigit - 1; currentDigit > 0; currentDigit--) {
                if (digitsLeft > 0) {
                    count += availableDigits * (availableDigits - 1) / 2;
                }
            }
        }
        dp[digits] = count;
    }

    long long totalCount = 0;
    for (int i = 2; i <= maxDigits; i++) {
        totalCount += dp[i];
    }

    return totalCount;
}

int main() {
    int k, w;
    cin >> k >> w;
    cout << countR(k, w) << endl;
    return 0;
}