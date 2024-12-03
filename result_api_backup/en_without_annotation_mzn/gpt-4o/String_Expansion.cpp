#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int p1, p2, p3, m;
vector<string> str;
string lower_alphabet = "abcdefghijklmnopqrstuvwxyz0123456789";
string upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int index_of_array(const string &alphabet, char ch) {
    auto it = find(alphabet.begin(), alphabet.end(), ch);
    return it != alphabet.end() ? distance(alphabet.begin(), it) + 1 : -1;
}

string expand_string(const string &s) {
    string result;
    for (size_t i = 0; i < s.size(); ++i) {
        if (i == 0 || i == s.size() - 1 || s[i - 1] != '-' && s[i + 1] != '-') {
            result += s[i];
        } else if (s[i] == '-') {
            int idx1 = index_of_array(lower_alphabet, s[i - 1]);
            int idx2 = index_of_array(lower_alphabet, s[i + 1]);
            if (idx1 != -1 && idx2 != -1 && idx1 < idx2) {
                string expanded;
                if (idx1 <= 26 && idx2 <= 26) {  // Both are lowercase
                    for (int t = idx1; t < idx2 - 1; ++t) {
                        for (int l = 0; l < p2; ++l) {
                            expanded += (p1 == 1 ? lower_alphabet[t + 1] : p1 == 2 ? upper_alphabet[t + 1] : '*');
                        }
                    }
                } else if (idx1 > 26 && idx2 > 26) {  // Both are digits
                    for (int t = idx1; t < idx2 - 1; ++t) {
                        for (int l = 0; l < p2; ++l) {
                            expanded += '*';
                        }
                    }
                }
                result += (p3 == 2 ? string(expanded.rbegin(), expanded.rend()) : expanded);
            } else {
                result += s[i];
            }
        } else {
            result += s[i];
        }
    }
    return result;
}

int main() {
    cin >> p1 >> p2 >> p3 >> m;
    str.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> str[i];
    }

    for (const auto &s : str) {
        cout << expand_string(s) << endl;
    }

    return 0;
}