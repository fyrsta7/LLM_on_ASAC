#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int get_num(char letter) {
    return letter - 'a' + 1;
}

int distance(const vector<int>& x1, const vector<int>& x2, int w, int t, int s) {
    int sum = 0;
    for (int i = 0; i < w; ++i) {
        sum += (x2[i] - x1[i]) * pow(t - s + 1, w - i - 1);
    }
    return sum;
}

bool larger(const vector<int>& l, const vector<int>& r, int pointer) {
    if (pointer == l.size()) return false;
    if (l[pointer] > r[pointer]) return true;
    if (l[pointer] == r[pointer]) return larger(l, r, pointer + 1);
    return false;
}

int main() {
    int s, t, w;
    cin >> s >> t >> w;
    vector<string> str(w);
    for (int i = 0; i < w; ++i) {
        cin >> str[i];
    }

    vector<int> str_int(w);
    for (int i = 0; i < w; ++i) {
        str_int[i] = get_num(str[i][0]);
    }

    vector<vector<int>> str_list(6, vector<int>(w));
    str_list[0] = str_int;

    for (int i = 1; i < 6; ++i) {
        str_list[i] = str_list[i - 1];
        next_permutation(str_list[i].begin(), str_list[i].end());
    }

    for (int i = 1; i < 6; ++i) {
        for (int j = 0; j < w - 1; ++j) {
            if (str_list[i][j] >= str_list[i][j + 1]) {
                sort(str_list[i].begin() + j + 1, str_list[i].end());
                next_permutation(str_list[i].begin() + j + 1, str_list[i].end());
            }
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 6; ++j) {
            if (!larger(str_list[j], str_list[i], 0)) {
                swap(str_list[i], str_list[j]);
            }
        }
    }

    int d = distance(str_list[0], str_list[5], w, t, s);

    for (int k = 1; k < 6; ++k) {
        for (int i = 0; i < w; ++i) {
            cout << char(str_list[k][i] + 'a' - 1);
        }
        cout << endl;
    }

    return 0;
}
