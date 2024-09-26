#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int get_num(char letter) {
    return letter - 'a' + 1;
}

int distance(const vector<int>& x1, const vector<int>& x2, int s, int t, int w) {
    int sum = 0;
    int pow_base = pow(t - s + 1, w - 1);
    for (int i = 0; i < w; ++i) {
        sum += (x2[i] - x1[i]) * pow_base;
        if (i + 1 < w) pow_base /= (t - s + 1);
    }
    return sum;
}

bool larger(const vector<int>& l, const vector<int>& r, int pointer) {
    if (pointer == l.size()) return false;
    return l[pointer] > r[pointer] || (l[pointer] == r[pointer] && larger(l, r, pointer + 1));
}

int main() {
    int s, t, w;
    cin >> s >> t >> w;
    vector<string> str(w);
    for (int i = 0; i < w; ++i) cin >> str[i];

    vector<int> str_int(w);
    for (int i = 0; i < w; ++i) str_int[i] = get_num(str[i][0]);

    vector<vector<int>> str_list(6, vector<int>(w));
    str_list[0] = str_int;

    for (int i = 1; i <= 5; ++i) {
        str_list[i] = str_list[i - 1];
        // Generate next lexicographical permutation that satisfies constraints
        do {
            next_permutation(str_list[i].begin(), str_list[i].end());
        } while (!is_sorted(str_list[i].begin(), str_list[i].end()) || adjacent_find(str_list[i].begin(), str_list[i].end()) != str_list[i].end());
    }

    sort(str_list.begin(), str_list.end(), [](const vector<int>& a, const vector<int>& b) { return a < b; });

    int d = distance(str_list[0], str_list[5], s, t, w);
    cout << d << endl;

    for (int k = 1; k <= 5; ++k) {
        for (int i = 0; i < w; ++i) {
            cout << char(str_list[k][i] + 'a' - 1);
        }
        cout << endl;
    }

    return 0;
}
