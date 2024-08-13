#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> bookCodes(n);
    for (int i = 0; i < n; ++i) {
        cin >> bookCodes[i];
    }

    for (int i = 0; i < q; ++i) {
        int len, requirement;
        cin >> len >> requirement;
        int minCode = INT_MAX;
        bool found = false;
        
        // Create the requirement filter based on length
        int mod = 1;
        for (int l = 0; l < len; ++l) {
            mod *= 10;
        }

        // Check book codes
        for (int j = 0; j < n; ++j) {
            if (bookCodes[j] % mod == requirement) {
                minCode = min(minCode, bookCodes[j]);
                found = true;
            }
        }

        if (found) {
            cout << minCode << endl;
        } else {
            cout << -1 << endl;
        }
    }

    return 0;
}