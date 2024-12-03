#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> encrypt(n), origin(n);
    for (int i = 0; i < n; ++i) cin >> encrypt[i];
    for (int i = 0; i < n; ++i) cin >> origin[i];

    int m;
    cin >> m;
    vector<string> translate(m);
    for (int i = 0; i < m; ++i) cin >> translate[i];

    vector<string> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    unordered_map<string, int> char_to_index;
    for (int i = 0; i < 26; ++i) char_to_index[alphabet[i]] = i + 1;

    vector<int> encrypt_int(n), origin_int(n);
    for (int i = 0; i < n; ++i) {
        encrypt_int[i] = char_to_index[encrypt[i]];
        origin_int[i] = char_to_index[origin[i]];
    }

    vector<int> translate_int(m);
    for (int i = 0; i < m; ++i) translate_int[i] = char_to_index[translate[i]];

    unordered_set<int> origin_set(origin_int.begin(), origin_int.end());
    unordered_set<int> encrypt_set(encrypt_int.begin(), encrypt_int.end());

    bool condition1 = origin_set.size() < 26 || encrypt_set.size() < 26;
    bool condition2 = false;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (origin_int[i] == origin_int[j] && encrypt_int[i] != encrypt_int[j]) {
                condition2 = true;
                break;
            }
        }
        if (condition2) break;
    }

    bool if_fail = !(condition1 || condition2);

    vector<int> code(27, 0);
    if (!if_fail) {
        for (int i = 0; i < n; ++i) {
            code[origin_int[i]] = encrypt_int[i];
        }
    } else {
        for (int i = 1; i <= 26; ++i) code[i] = i;
    }

    vector<int> out_int(m);
    for (int i = 0; i < m; ++i) out_int[i] = code[translate_int[i]];

    if (if_fail) {
        cout << "Failed" << endl;
    } else {
        for (int i = 0; i < m; ++i) cout << alphabet[out_int[i] - 1];
        cout << endl;
    }

    return 0;
}
