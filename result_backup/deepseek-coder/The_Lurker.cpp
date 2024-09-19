#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    string encrypted1, original, encrypted2;
    cin >> encrypted1 >> original >> encrypted2;

    unordered_map<char, char> codeMap;
    unordered_set<char> usedChars;

    for (size_t i = 0; i < encrypted1.size(); ++i) {
        if (codeMap.find(encrypted1[i]) != codeMap.end() && codeMap[encrypted1[i]] != original[i]) {
            cout << "Failed" << endl;
            return 0;
        }
        codeMap[encrypted1[i]] = original[i];
        usedChars.insert(original[i]);
    }

    if (codeMap.size() != 26 || usedChars.size() != 26) {
        cout << "Failed" << endl;
        return 0;
    }

    for (char c : encrypted2) {
        if (codeMap.find(c) == codeMap.end()) {
            cout << "Failed" << endl;
            return 0;
        }
    }

    for (char c : encrypted2) {
        cout << codeMap[c];
    }
    cout << endl;

    return 0;
}
