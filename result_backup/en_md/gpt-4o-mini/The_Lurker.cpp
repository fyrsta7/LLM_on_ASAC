#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    string encMessage, origMessage, translateMessage;
    cin >> encMessage >> origMessage >> translateMessage;

    unordered_map<char, char> cipher;
    unordered_set<char> usedWords;

    // Build the cipher based on the given messages
    for (size_t i = 0; i < encMessage.size(); ++i) {
        char eChar = encMessage[i];
        char oChar = origMessage[i];

        if (cipher.count(oChar)) {
            if (cipher[oChar] != eChar) {
                cout << "Failed" << endl;
                return 0;
            }
        } else {
            if (usedWords.count(eChar)) {
                cout << "Failed" << endl;
                return 0;
            }
            cipher[oChar] = eChar;
            usedWords.insert(eChar);
        }
    }

    // Check for missing letters
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (cipher.find(c) == cipher.end()) {
            cout << "Failed" << endl;
            return 0;
        }
    }

    // Translate the new encrypted message
    string translatedMessage;
    for (char c : translateMessage) {
        translatedMessage += cipher[c];
    }

    cout << translatedMessage << endl;
    return 0;
}