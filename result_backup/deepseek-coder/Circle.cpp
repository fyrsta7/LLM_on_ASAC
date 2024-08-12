#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

typedef long long ll;

vector<int> multiply(const vector<int>& a, const vector<int>& b, int k) {
    vector<int> res(k, 0);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            res[(i + j) % k] += a[i] * b[j];
            res[(i + j) % k] %= 10;
        }
    }
    return res;
}

vector<int> power(const vector<int>& base, ll exp, int k) {
    if (exp == 1) return base;
    if (exp % 2 == 0) {
        vector<int> half = power(base, exp / 2, k);
        return multiply(half, half, k);
    } else {
        return multiply(base, power(base, exp - 1, k), k);
    }
}

int findCircleLength(const vector<int>& base, int k) {
    vector<int> current = base;
    for (int len = 1; len <= 10000; ++len) {
        current = multiply(current, base, k);
        if (current == base) return len;
    }
    return -1;
}

int main() {
    string n;
    int k;
    cin >> n >> k;

    vector<int> base(k, 0);
    for (int i = 0; i < k && i < n.size(); ++i) {
        base[i] = n[n.size() - 1 - i] - '0';
    }

    cout << findCircleLength(base, k) << endl;
    return 0;
}
