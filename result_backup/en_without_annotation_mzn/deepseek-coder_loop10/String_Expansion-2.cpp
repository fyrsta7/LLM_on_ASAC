#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int p1, p2, p3, m;
vector<string> str;
vector<string> lower_alphabet = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","0","1","2","3","4","5","6","7","8","9"};
vector<string> upper_alphabet = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9"};
vector<string> star = {"*"};

int index_of_array(const vector<string>& alphabet, const string& s) {
    for (int i = 0; i < alphabet.size(); ++i) {
        if (alphabet[i] == s) return i;
    }
    return -1;
}

string expand(int p) {
    if (p == 0 || p == m - 1) return str[p];
    if (str[p - 1] == "-" || str[p + 1] == "-") return str[p];
    if (str[p] == "-") {
        int left = index_of_array(lower_alphabet, str[p - 1]);
        int right = index_of_array(lower_alphabet, str[p + 1]);
        if (left == -1 || right == -1 || left >= right) return str[p];

        string result;
        if (p3 == 2) {
            for (int i = right - 1; i > left; --i) {
                for (int j = 0; j < p2; ++j) {
                    result += (p1 == 1 ? lower_alphabet[i] : (p1 == 2 ? upper_alphabet[i] : star[0]));
                }
            }
        } else {
            for (int i = left + 1; i < right; ++i) {
                for (int j = 0; j < p2; ++j) {
                    result += (p1 == 1 ? lower_alphabet[i] : (p1 == 2 ? upper_alphabet[i] : star[0]));
                }
            }
        }
        return result;
    }
    return str[p];
}

int main() {
    cin >> p1 >> p2 >> p3 >> m;
    str.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> str[i];
    }

    for (int i = 0; i < m; ++i) {
        cout << expand(i);
    }
    cout << endl;

    return 0;
}
