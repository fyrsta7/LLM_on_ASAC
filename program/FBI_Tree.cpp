#include <iostream>
#include <string>
using namespace std;

void constructFbiTree(string &result, const string &s, int left, int right) {
    if (left > right) return;
    
    bool hasZero = false, hasOne = false;
    for (int i = left; i <= right; ++i) {
        if (s[i] == '0') hasZero = true;
        if (s[i] == '1') hasOne = true;
    }
    
    if (hasZero && hasOne) {
        result += 'F';
    } else if (hasZero) {
        result += 'B';
    } else {
        result += 'I';
    }
    
    if (left < right) {
        int mid = (left + right) / 2;
        constructFbiTree(result, s, left, mid);
        constructFbiTree(result, s, mid + 1, right);
    }
}

void postOrderTraversal(string &result, const string &s, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    postOrderTraversal(result, s, left, mid);
    postOrderTraversal(result, s, mid + 1, right);
    constructFbiTree(result, s, left, right);
}

int main() {
    int N;
    cin >> N;
    string s;
    cin >> s;
    
    string result;
    postOrderTraversal(result, s, 0, s.length() - 1);
    
    for (int i = result.length() - 1; i >= 0; --i) {
        cout << result[i];
    }
    
    return 0;
}