#include <iostream>
#include <string>
using namespace std;

string expandString(const string &s, int p1, int p2, int p3) {
    string result;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == '-' && i > 0 && i < s.length() - 1) {
            char left = s[i-1], right = s[i+1];
            if ((isdigit(left) && isdigit(right) || isalpha(left) && isalpha(right)) && left < right - 1) {
                string fill;
                for (char c = left + 1; c < right; ++c) {
                    char fillChar = c;
                    if (p1 == 2 && isalpha(c)) fillChar = toupper(c);
                    if (p1 == 3) fillChar = '*';
                    fill.append(p2, fillChar);
                }
                if (p3 == 2) reverse(fill.begin(), fill.end());
                result += fill;
            } else if (left < right) {
                result += "-";
            }
        } else {
            result += s[i];
        }
    }
    return result;
}

int main() {
    int p1, p2, p3;
    string s;

    cin >> p1 >> p2 >> p3 >> ws;
    getline(cin, s);

    cout << expandString(s, p1, p2, p3) << endl;

    return 0;
}