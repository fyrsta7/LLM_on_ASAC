#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int index_of_alphabet(char ch) {
    return ch - 'A' + 1;
}

int main() {
    int n, m;
    cin >> n;
    vector<string> encrypt(n), origin(n);
    for (int i = 0; i < n; i++) cin >> encrypt[i];
    for (int i = 0; i < n; i++) cin >> origin[i];
    cin >> m;
    vector<string> translate(m);
    for (int i = 0; i < m; i++) cin >> translate[i];

    vector<int> encrypt_int(n), origin_int(n), translate_int(m), out_int(m);
    for (int i = 0; i < n; i++) {
        encrypt_int[i] = index_of_alphabet(encrypt[i][0]);
        origin_int[i] = index_of_alphabet(origin[i][0]);
    }
    for (int i = 0; i < m; i++) {
        translate_int[i] = index_of_alphabet(translate[i][0]);
    }

    bool condition1 = false, condition2 = false;
    unordered_set<int> origin_set, encrypt_set;
    for (int i = 0; i < n; i++) {
        origin_set.insert(origin_int[i]);
        encrypt_set.insert(encrypt_int[i]);
    }
    if (origin_set.size() < 26 || encrypt_set.size() < 26) condition1 = true;

    for (int i = 0; i < n && !condition2; i++) {
        for (int j = i + 1; j < n && !condition2; j++) {
            if (origin_int[i] == origin_int[j] && encrypt_int[i] != encrypt_int[j]) {
                condition2 = true;
            }
        }
    }

    bool if_fail = condition1 || condition2;
    unordered_map<int, int> code;
    if (!if_fail) {
        for (int i = 0; i < n; i++) {
            code[origin_int[i]] = encrypt_int[i];
        }
    } else {
        for (int i = 1; i <= 26; i++) {
            code[i] = i;
        }
    }

    for (int i = 0; i < m; i++) {
        out_int[i] = code[translate_int[i]];
    }

    if (if_fail) {
        cout << "Failed" << endl;
    } else {
        for (int i = 0; i < m; i++) {
            cout << char(out_int[i] + 'A' - 1);
        }
        cout << endl;
    }

    return 0;
}