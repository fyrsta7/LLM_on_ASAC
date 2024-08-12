#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isPrime(int n) {
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
    int maxn = 0, minn = 100;
    for (int f : freq) {
        if (f > 0) {
            maxn = max(maxn, f);
            minn = min(minn, f);
        }
    }
    int diff = maxn - minn;
    if (isPrime(diff)) {
        cout << "Lucky Word" << endl;
        cout << diff << endl;
    } else {
        cout << "No Answer" << endl;
        cout << 0 << endl;
    }
    return 0;
}
