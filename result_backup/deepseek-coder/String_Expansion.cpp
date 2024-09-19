#include <iostream>
#include <string>
using namespace std;

string expandString(int p1, int p2, int p3, string s) {
    string result = "";
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        if (s[i] == '-' && i > 0 && i < n - 1) {
            char left = s[i - 1];
            char right = s[i + 1];
            if ((islower(left) && islower(right)) || (isdigit(left) && isdigit(right))) {
                if (left < right) {
                    string expanded = "";
                    for (char c = left + 1; c < right; ++c) {
                        for (int j = 0; j < p2; ++j) {
                            if (p1 == 1) {
                                expanded += tolower(c);
                            } else if (p1 == 2) {
                                expanded += toupper(c);
                            } else if (p1 == 3) {
                                expanded += '*';
                            }
                        }
                    }
                    if (p3 == 2) {
                        reverse(expanded.begin(), expanded.end());
                    }
                    result += expanded;
                    continue;
                } else if (left == right - 1) {
                    continue;
                }
            }
        }
        result += s[i];
    }
    return result;
}

int main() {
    int p1, p2, p3;
    string s;
    cin >> p1 >> p2 >> p3;
    cin >> s;
    cout << expandString(p1, p2, p3, s) << endl;
    return 0;
}
