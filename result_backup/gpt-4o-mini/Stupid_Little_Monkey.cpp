#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    string word;
    cin >> word;

    vector<int> freq(26, 0);
    for (char c : word) {
        freq[c - 'a']++;
    }

    int maxn = *max_element(freq.begin(), freq.end());
    int minn = *min_element(freq.begin(), freq.end());
    
    // Ignore letters that did not appear
    if (minn == 0) {
        minn = *min_element(freq.begin(), freq.end() - 1);
    }

    int difference = maxn - minn;
    
    if (is_prime(difference)) {
        cout << "Lucky Word" << endl;
        cout << difference << endl;
    } else {
        cout << "No Answer" << endl;
        cout << 0 << endl;
    }

    return 0;
}