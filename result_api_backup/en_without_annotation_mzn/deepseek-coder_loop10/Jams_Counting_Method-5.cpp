#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int get_num(char letter) {
    return letter - 'a' + 1;
}

int distance(const vector<int>& x1, const vector<int>& x2, int w, int s, int t) {
    int sum = 0;
    for (int i = 0; i < w; ++i) {
        sum += (x2[i] - x1[i]) * pow(t - s + 1, w - i - 1);
    }
    return sum;
}

bool larger(const vector<int>& l, const vector<int>& r, int pointer, int w) {
    if (pointer == w) return false;
    return l[pointer] > r[pointer] || (l[pointer] == r[pointer] && larger(l, r, pointer + 1, w));
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
        for (int j = 0; j < w; ++j) {
            str_list[i][j] = str_list[i-1][j];
        }
        next_permutation(str_list[i].begin(), str_list[i].end());
    }

    int d = distance(str_list[0], str_list[5], w, s, t);

    for (int k = 1; k < 6; ++k) {
        for (int i = 0; i < w; ++i) {
            cout << char(str_list[k][i] + 'a' - 1);
        }
        cout << endl;
    }

    return 0;
}