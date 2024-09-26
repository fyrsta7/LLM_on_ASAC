#include <iostream>
#include <string>
using namespace std;

string vigenereDecode(const string& key, const string& ciphertext) {
    string plaintext = "";
    int keyLen = key.length();
    int textLen = ciphertext.length();

    for (int i = 0; i < textLen; i++) {
        char c = ciphertext[i];
        char k = key[i % keyLen];
        int shift = (islower(k) ? k - 'a' : k - 'A');  // Compute shift ignoring case of key

        if (isupper(c)) {
            plaintext += (c - 'A' - shift + 26) % 26 + 'A';
        } else if (islower(c)) {
            plaintext += (c - 'a' - shift + 26) % 26 + 'a';
        }
    }

    return plaintext;
}

int main() {
    string key, ciphertext;
    getline(cin, key);
    getline(cin, ciphertext);

    string plaintext = vigenereDecode(key, ciphertext);
    cout << plaintext << endl;

    return 0;
}