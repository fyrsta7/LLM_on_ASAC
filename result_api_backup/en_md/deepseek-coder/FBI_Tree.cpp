#include <iostream>
#include <string>
using namespace std;

void constructFBI(const string& s, string& result) {
    if (s.length() == 1) {
        result += (s[0] == '0' ? 'B' : 'I');
        return;
    }

    size_t mid = s.length() / 2;
    string left = s.substr(0, mid);
    string right = s.substr(mid);

    constructFBI(left, result);
    constructFBI(right, result);

    if (left.find('1') != string::npos || right.find('1') != string::npos) {
        if (left.find('1') != string::npos && right.find('1') != string::npos)
            result += 'F';
        else
            result += (left.find('1') != string::npos ? 'F' : 'I');
    } else {
        result += 'B';
    }
}

int main() {
    int N;
    string S;
    cin >> N >> S;

    string result;
    constructFBI(S, result);

    cout << result << endl;
    return 0;
}
