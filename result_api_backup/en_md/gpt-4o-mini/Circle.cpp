#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>

using namespace std;

string lastKDigits(string n, int k) {
    if (n.length() < k) {
        return string(k - n.length(), '0') + n;
    }
    return n.substr(n.length() - k);
}

string multiply(string a, string b) {
    int n = a.length(), m = b.length();
    vector<int> result(n + m, 0);
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int sum = mul + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }
    
    string res;
    for (int num : result) {
        if (!(res.empty() && num == 0)) {
            res.push_back(num + '0');
        }
    }
    return res.empty() ? "0" : res;
}

string power(string n, int exponent) {
    string result = "1";
    for (int i = 0; i < exponent; i++) {
        result = multiply(result, n);
    }
    return result;
}

int findCircleLength(string n, int k) {
    unordered_map<string, int> seen;
    string currentPower = "1";
    int length = 0;

    while (true) {
        currentPower = multiply(currentPower, n);
        string lastDigits = lastKDigits(currentPower, k);
        
        if (seen.count(lastDigits)) {
            return length - seen[lastDigits];
        }
        seen[lastDigits] = length;
        length++;
        
        if (length > 1000000) break; // arbitrary large limit to prevent infinite loops
    }

    return -1;
}

int main() {
    string n;
    int k;
    cin >> n >> k;

    int circleLength = findCircleLength(n, k);
    cout << circleLength << endl;

    return 0;
}