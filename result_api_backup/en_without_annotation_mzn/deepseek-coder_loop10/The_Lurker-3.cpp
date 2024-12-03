#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

int index_of_alphabet(const string& str) {
    static const vector<string> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    for (int i = 0; i < 26; ++i) {
        if (alphabet[i] == str) return i + 1;
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n;
    vector<string> encrypt(n), origin(n);
    for (int i = 0; i < n; ++i) cin >> encrypt[i];
    for (int i = 0; i < n; ++i) cin >> origin[i];
    cin >> m;
    vector<string> translate(m);
    for (int i = 0; i < m; ++i) cin >> translate[i];

    vector<int> encrypt_int(n), origin_int(n);
    for (int i = 0; i < n; ++i) {
        encrypt_int[i] = index_of_alphabet(encrypt[i]);
        origin_int[i] = index_of_alphabet(origin[i]);
    }

    vector<int> translate_int(m);
    for (int i = 0; i < m; ++i) {
        translate_int[i] = index_of_alphabet(translate[i]);
    }

    unordered_map<int, int> code;
    bool if_fail = false;
    unordered_set<int> origin_set(origin_int.begin(), origin_int.end());
    unordered_set<int> encrypt_set(encrypt_int.begin(), encrypt_int.end());

    if (origin_set.size() < 26 || encrypt_set.size() < 26) {
        if_fail = true;
    } else {
        for (int i = 0; i < n; ++i) {
            if (code.count(origin_int[i]) && code[origin_int[i]] != encrypt_int[i]) {
                if_fail = true;
                break;
            }
            code[origin_int[i]] = encrypt_int[i];
        }
    }

    if (if_fail) {
        cout << "Failed" << endl;
    } else {
        vector<string> out(m);
        for (int i = 0; i < m; ++i) {
            out[i] = code[translate_int[i]] ? alphabet[code[translate_int[i]] - 1] : translate[i];
        }
        for (const string& s : out) cout << s;
        cout << endl;
    }

    return 0;
}
