Here's a C++ program for the given problem:

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    string encrypted_message, original_message, intercepted_message;
    cin >> encrypted_message >> original_message >> intercepted_message;
    
    if (encrypted_message.length() != original_message.length()) {
        cout << "Failed" << endl;
        return 0;
    }
    
    unordered_map<char, char> cipher;
    unordered_set<char> used_secret_words;
    
    for (size_t i = 0; i < encrypted_message.length(); ++i) {
        char e = encrypted_message[i];
        char o = original_message[i];
        if (cipher.count(o)) {
            if (cipher[o] != e) {
                cout << "Failed" << endl;
                return 0;
            }
        } else {
            if (used_secret_words.count(e)) {
                cout << "Failed" << endl;
                return 0;
            }
            cipher[o] = e;
            used_secret_words.insert(e);
        }
    }
    
    if (cipher.size() < 26) {
        cout << "Failed" << endl;
        return 0;
    }
    
    unordered_map<char, char> reverse_cipher;
    for (const auto& p : cipher) {
        reverse_cipher[p.second] = p.first;
    }
    
    string result;
    for (char c : intercepted_message) {
        if (reverse_cipher.count(c)) {
            result += reverse_cipher[c];
        } else {
            cout << "Failed" << endl;
            return 0;
        }
    }
    
    cout << result << endl;
    return 0;
}