#include <iostream>
#include <string>
using namespace std;

string decryptVigenere(const string& ciphertext, const string& key) {
    string plaintext;
    int keyLen = key.length();
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char c = ciphertext[i];
        char k = key[i % keyLen];
        if (isupper(c)) {
            plaintext += 'A' + (c - k + 26) % 26;
        } else if (islower(c)) {
            plaintext += 'a' + (c - k + 26) % 26;
        }
    }
    return plaintext;
}

int main() {
    string key, ciphertext;
    cin >> key >> ciphertext;
    for (char& k : key) {
        k = isupper(k) ? k - 'A' : k - 'a';
    }
    string plaintext = decryptVigenere(ciphertext, key);
    cout << plaintext << endl;
    return 0;
}
