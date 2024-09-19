#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(){
    string key, cipher;
    getline(cin, key);
    getline(cin, cipher);
    int key_len = key.length();
    string plaintext;
    plaintext.reserve(cipher.length());
    for(int i=0; i < cipher.length(); ++i){
        char c = cipher[i];
        char k = key[i % key_len];
        int c_num = toupper(c) - 'A';
        int k_num = toupper(k) - 'A';
        int m_num = (c_num - k_num + 26) % 26;
        char m_char = 'A' + m_num;
        if(islower(c)){
            m_char = tolower(m_char);
        }
        plaintext += m_char;
    }
    cout << plaintext;
}