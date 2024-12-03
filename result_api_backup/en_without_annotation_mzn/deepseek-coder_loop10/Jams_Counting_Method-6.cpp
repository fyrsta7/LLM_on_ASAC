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
    return l[pointer] > r[pointer] || (l[pointer] == r[pointer] && larger(l, r, pointer + 1));
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
        vector<int> temp = str_list[i - 1];
        while (true) {
            int j = w - 1;
            while (j >= 0 && temp[j] == t) --j;
            if (j < 0) break;
            ++temp[j];
            for (int k = j + 1; k < w; ++k) temp[k] = temp[j];
            if (is_sorted(temp.begin(), temp.end()) && !any_of(str_list.begin(), str_list.begin() + i, [&](const vector<int>& v) { return v == temp; })) {
                str_list[i] = temp;
                break;
            }
        }
    }

    sort(str_list.begin(), str_list.end(), [](const vector<int>& a, const vector<int>& b) { return larger(b, a, 0); });

    for (int k = 1; k <= 5; ++k) {
        for (int i = 0; i < w; ++i) {
            cout << char('a' + str_list[k][i] - 1);
        }
        cout << endl;
    }

    return 0;
}
