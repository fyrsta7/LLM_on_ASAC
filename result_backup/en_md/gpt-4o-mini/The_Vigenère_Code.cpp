#include <iostream>
#include <string>

using namespace std;

char vigenereDecrypt(char ciphertext, char key_char) {
    if (isupper(ciphertext)) {
        return (ciphertext - key_char + 26) % 26 + 'A';
    } else {
        return (ciphertext - key_char + 26) % 26 + 'a';
    }
}

string decryptVigenere(const string& key, const string& ciphertext) {
    string plaintext;
    int key_length = key.size();
    for (int i = 0, j = 0; i < ciphertext.size(); i++) {
        if (isalpha(ciphertext[i])) {
            char key_char = tolower(key[j % key_length]);
            plaintext += vigenereDecrypt(ciphertext[i], key_char);
            j++;
        } else {
            plaintext += ciphertext[i];
        }
    }
    return plaintext;
}

int main() {
    string key, ciphertext;
    getline(cin, key);
    getline(cin, ciphertext);
    
    string plaintext = decryptVigenere(key, ciphertext);
    cout << plaintext << endl;
    
    return 0;
}