#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

int get_num(char letter) {
    return letter - 'a' + 1;
}

int distance(const vector<int>& x1, const vector<int>& x2, int w, int t, int s) {
    int sum = 0;
    int pow_val = 1;
    for (int i = w - 1; i >= 0; --i) {
        sum += (x2[i] - x1[i]) * pow_val;
        pow_val *= (t - s + 1);
    }
    return sum;
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

    for (int i = 1; i <= 5; ++i) {
        vector<int> next_str = str_list[i - 1];
        int j = w - 1;
        while (j >= 0 && next_str[j] == t) {
            next_str[j] = s;
            --j;
        }
        if (j >= 0) {
            ++next_str[j];
        }
        str_list[i] = next_str;
    }

    for (int i = 1; i <= 5; ++i) {
        for (int j = 0; j < w; ++j) {
            cout << char(str_list[i][j] + 'a' - 1);
        }
        cout << endl;
    }

    return 0;
}