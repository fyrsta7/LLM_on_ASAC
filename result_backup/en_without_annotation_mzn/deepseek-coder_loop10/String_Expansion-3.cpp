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
    return it - alphabet.begin() + 1;
}

string expand_sequence(int start, int end, int repeat, bool reverse, int mode) {
    string result;
    if (reverse) {
        for (int i = end - 1; i > start; --i) {
            for (int j = 0; j < repeat; ++j) {
                if (mode == 1) result += lower_alphabet[i - 1];
                else if (mode == 2) result += upper_alphabet[i - 1];
                else result += star[0];
            }
        }
    } else {
        for (int i = start + 1; i < end; ++i) {
            for (int j = 0; j < repeat; ++j) {
                if (mode == 1) result += lower_alphabet[i - 1];
                else if (mode == 2) result += upper_alphabet[i - 1];
                else result += star[0];
            }
        }
    }
    return result;
}

int main() {
    cin >> p1 >> p2 >> p3 >> m;
    str.resize(m);
    for (int i = 0; i < m; ++i) cin >> str[i];

    vector<string> output;
    for (int p = 0; p < m; ++p) {
        if (p == 0 || p == m - 1 || str[p - 1] == "-" || str[p + 1] == "-") {
            output.push_back(str[p]);
        } else if (str[p] == "-") {
            int left_index = index_of_array(lower_alphabet, str[p - 1]);
            int right_index = index_of_array(lower_alphabet, str[p + 1]);
            if ((left_index <= 26 && right_index <= 26 && left_index < right_index) ||
                (left_index > 26 && right_index > 26 && left_index < right_index)) {
                output.push_back(expand_sequence(left_index, right_index, p2, p3 == 2, p1));
            } else {
                output.push_back(str[p]);
            }
        } else {
            output.push_back(str[p]);
        }
    }

    for (const string& s : output) cout << s;
    cout << endl;

    return 0;
}
