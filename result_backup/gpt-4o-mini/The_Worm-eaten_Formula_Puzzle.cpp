#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool isValid(const vector<int>& values, const string& a, const string& b, const string& c) {
    int carry = 0;
    int n = a.size();
    for (int i = n - 1; i >= 0; --i) {
        int sum = values[a[i] - 'A'] + values[b[i] - 'A'] + carry;
        carry = sum / 5; // since n is the base
        if (sum % 5 != values[c[i] - 'A']) return false;
    }
    return carry == 0;
}

void solve(int n, const string& a, const string& b, const string& c) {
    vector<int> values(26, -1); // to hold values of A-Z
    vector<int> result(n, -1);
    unordered_map<char, int> used;

    vector<char> uniqueChars;
    for (char ch : a) if (used[ch]++ == 0) uniqueChars.push_back(ch);
    for (char ch : b) if (used[ch]++ == 0) uniqueChars.push_back(ch);
    for (char ch : c) if (used[ch]++ == 0) uniqueChars.push_back(ch);

    int k = uniqueChars.size();
    vector<int> indices(k);
    for (int i = 0; i < k; ++i) indices[i] = i;

    do {
        for (int i = 0; i < k; ++i) {
            values[uniqueChars[i] - 'A'] = indices[i];
        }
        if (isValid(values, a, b, c)) {
            for (int i = 0; i < n; ++i) {
                result[i] = values[a[i] - 'A'];
            }
            break;
        }
    } while (next_permutation(indices.begin(), indices.end()));

    for (int i = 0; i < n; ++i) {
        cout << result[i] << (i + 1 < n ? " " : "");
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;

    string a, b, c;
    cin >> a >> b >> c;

    solve(n, a, b, c);
    return 0;
}