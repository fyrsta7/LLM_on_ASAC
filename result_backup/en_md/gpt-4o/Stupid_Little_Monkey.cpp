#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    string word;
    cin >> word;
    
    vector<int> freq(26, 0);
    for (char ch : word) {
        freq[ch - 'a']++;
    }

    int max_freq = 0, min_freq = INT_MAX;
    for (int count : freq) {
        if (count > 0) {
            if (count > max_freq) max_freq = count;
            if (count < min_freq) min_freq = count;
        }
    }

    int diff = max_freq - min_freq;
    if (isPrime(diff)) {
        cout << "Lucky Word" << endl;
        cout << diff << endl;
    } else {
        cout << "No Answer" << endl;
        cout << 0 << endl;
    }

    return 0;
}