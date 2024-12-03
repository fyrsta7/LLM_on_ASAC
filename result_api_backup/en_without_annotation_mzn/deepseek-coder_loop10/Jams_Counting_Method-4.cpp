#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

int s, t, w;
vector<string> str;
unordered_map<string, int> letter_to_num = {
    {"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}, {"f", 6}, {"g", 7}, {"h", 8},
    {"i", 9}, {"j", 10}, {"k", 11}, {"l", 12}, {"m", 13}, {"n", 14}, {"o", 15}, {"p", 16},
    {"q", 17}, {"r", 18}, {"s", 19}, {"t", 20}, {"u", 21}, {"v", 22}, {"w", 23}, {"x", 24},
    {"y", 25}, {"z", 26}
};

int distance(const vector<int>& x1, const vector<int>& x2) {
    int dist = 0;
    for (int i = 0; i < w; ++i) {
        dist += (x2[i] - x1[i]) * pow(t - s + 1, w - i - 1);
    }
    return dist;
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
        str_int[i] = letter_to_num[str[i]];
    }

    vector<vector<int>> str_list(6, vector<int>(w));
    str_list[0] = str_int;

    for (int i = 1; i < 6; ++i) {
        vector<int> candidate(w);
        for (int j = 0; j < w; ++j) {
            candidate[j] = str_list[i-1][j] + 1;
            if (candidate[j] > t) candidate[j] = s;
        }
        while (true) {
            bool valid = true;
            for (int j = 0; j < i; ++j) {
                if (candidate == str_list[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid) break;
            for (int j = 0; j < w; ++j) {
                candidate[j]++;
                if (candidate[j] > t) candidate[j] = s;
                else break;
            }
        }
        str_list[i] = candidate;
    }

    sort(str_list.begin(), str_list.end(), [](const vector<int>& a, const vector<int>& b) {
        return larger(a, b, 0);
    });

    for (int k = 1; k <= 5; ++k) {
        for (int i = 0; i < w; ++i) {
            cout << char('a' + str_list[k][i] - 1);
        }
        cout << endl;
    }

    return 0;
}