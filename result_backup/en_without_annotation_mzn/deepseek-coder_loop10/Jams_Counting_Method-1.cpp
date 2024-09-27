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
vector<string> num_to_letter = {
    "", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
    "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
};

int distance(const vector<int>& x1, const vector<int>& x2) {
    int sum = 0;
    for (int i = 0; i < w; ++i) {
        sum += (x2[i] - x1[i]) * pow(t - s + 1, w - i - 1);
    }
    return sum;
}

bool larger(const vector<int>& l, const vector<int>& r, int pointer) {
    if (pointer == w) return false;
    return l[pointer] > r[pointer] || (l[pointer] == r[pointer] && larger(l, r, pointer + 1));
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
        vector<int> next_str = str_list[i - 1];
        while (true) {
            for (int j = w - 1; j >= 0; --j) {
                if (next_str[j] < t) {
                    next_str[j]++;
                    for (int k = j + 1; k < w; ++k) {
                        next_str[k] = next_str[j] + k - j;
                    }
                    break;
                }
            }
            bool valid = true;
            for (int j = 0; j < i; ++j) {
                if (next_str == str_list[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                str_list[i] = next_str;
                break;
            }
        }
    }

    sort(str_list.begin(), str_list.end(), [](const vector<int>& a, const vector<int>& b) {
        return larger(b, a, 0);
    });

    for (int k = 0; k < 5; ++k) {
        for (int i = 0; i < w; ++i) {
            cout << num_to_letter[str_list[k][i]];
        }
        cout << endl;
    }

    return 0;
}