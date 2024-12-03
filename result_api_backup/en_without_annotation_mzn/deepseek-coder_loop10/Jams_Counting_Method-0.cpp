#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int s, t, w;
vector<string> str;
vector<string> alphabet = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

int get_num(string letter) {
    if (letter == "a") return 1;
    if (letter == "b") return 2;
    if (letter == "c") return 3;
    if (letter == "d") return 4;
    if (letter == "e") return 5;
    if (letter == "f") return 6;
    if (letter == "g") return 7;
    if (letter == "h") return 8;
    if (letter == "i") return 9;
    if (letter == "j") return 10;
    if (letter == "k") return 11;
    if (letter == "l") return 12;
    if (letter == "m") return 13;
    if (letter == "n") return 14;
    if (letter == "o") return 15;
    if (letter == "p") return 16;
    if (letter == "q") return 17;
    if (letter == "r") return 18;
    if (letter == "s") return 19;
    if (letter == "t") return 20;
    if (letter == "u") return 21;
    if (letter == "v") return 22;
    if (letter == "w") return 23;
    if (letter == "x") return 24;
    if (letter == "y") return 25;
    return 26;
}

int distance(const vector<int>& x1, const vector<int>& x2) {
    int sum = 0;
    for (int i = 0; i < w; ++i) {
        sum += (x2[i] - x1[i]) * pow(t - s + 1, w - i - 1);
    }
    return sum;
}

bool larger(const vector<int>& l, const vector<int>& r, int pointer) {
    if (pointer == w) return false;
    if (l[pointer] > r[pointer]) return true;
    if (l[pointer] == r[pointer]) return larger(l, r, pointer + 1);
    return false;
}

int main() {
    cin >> s >> t >> w;
    str.resize(w);
    for (int i = 0; i < w; ++i) {
        cin >> str[i];
    }

    vector<int> str_int(w);
    for (int i = 0; i < w; ++i) {
        str_int[i] = get_num(str[i]);
    }

    vector<vector<int>> str_list(6, vector<int>(w));
    str_list[0] = str_int;

    for (int i = 1; i < 6; ++i) {
        str_list[i] = str_list[i-1];
        next_permutation(str_list[i].begin(), str_list[i].end());
    }

    int d = distance(str_list[0], str_list[5]);

    for (int k = 1; k < 6; ++k) {
        for (int i = 0; i < w; ++i) {
            cout << alphabet[str_list[k][i] - 1] << (i == w - 1 ? "\n" : "");
        }
    }

    return 0;
}
