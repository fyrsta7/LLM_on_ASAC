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
    auto it = find(alphabet.begin(), alphabet.end(), s);
    return it - alphabet.begin();
}

string expand(int p) {
    if (p == 1 || p == m) return str[p - 1];
    if (str[p - 2] == "-" || str[p] == "-") return str[p - 1];

    int idx_prev = index_of_array(lower_alphabet, str[p - 2]);
    int idx_next = index_of_array(lower_alphabet, str[p]);

    if (str[p - 1] == "-" && 
        ((idx_prev <= 26 && idx_next <= 26 && idx_prev < idx_next) ||
         (idx_prev > 26 && idx_next > 26 && idx_prev < idx_next))) {
        
        string result;
        for (int t = idx_prev + 1; t < idx_next; ++t) {
            for (int l = 0; l < p2; ++l) {
                if (p1 == 1) result += lower_alphabet[t];
                else if (p1 == 2) result += upper_alphabet[t];
                else result += star[0];
            }
        }
        if (p3 == 2) reverse(result.begin(), result.end());
        return result;
    }
    return str[p - 1];
}

int main() {
    cin >> p1 >> p2 >> p3 >> m;
    str.resize(m);
    for (int i = 0; i < m; ++i) cin >> str[i];

    for (int p = 1; p <= m; ++p) {
        cout << expand(p);
    }
    cout << endl;

    return 0;
}
